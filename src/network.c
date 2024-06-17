#include "network.h"
#include "log.h"

#include <stdlib.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>

typedef struct {
	chunk_t*	data;
	ip4_addr	src;
	ip4_addr	dst;
}_packet_t;

_packet_t*	_pkt_create();
void				_pkt_free(_packet_t* pkt);
void*				_receiving(void* arg);
void*				_sending(void* arg);

network_t* net_create()
{
	network_t* net = calloc(1, sizeof(network_t*));
	net->q_send = que_create();
	net->q_recv = que_create();

	net->port = 500;
	net->src = htonl(INADDR_ANY);

	net->sock = socket(AF_INET, SOCK_DGRAM, 0);
	if(net->sock < 0) {
		logging(ERR, "[NET] Failure create socket\n");
		return NULL;
	}
	logging(ALL, "[NET] Create Socket\n");

	return net;
}

void net_free(network_t* net)
{
	_packet_t* d;
	for(d = dequeue(net->q_send); d != NULL; d = dequeue(net->q_send))
		_pkt_free(d);
	for(d = dequeue(net->q_recv); d != NULL; d = dequeue(net->q_recv))
		_pkt_free(d);

	free(net->q_send);
	free(net->q_recv);
	free(net);
}

_packet_t* _pkt_create()
{
	_packet_t* pkt = calloc(1, sizeof(_packet_t));

	return pkt;
}

void _pkt_free(_packet_t* pkt)
{
	if(pkt->data)
		chk_free(pkt->data);
	free(pkt);
}

void net_send(network_t* net, chunk_t* data, ip4_addr dst)
{
	_packet_t* pkt = _pkt_create();
	pkt->data = data;
	pkt->src = net->src;
	pkt->dst = dst;

	enqueue(net->q_send, pkt);
}

chunk_t* net_recv(network_t* net, ip4_addr* src)
{
	_packet_t* pkt = dequeue(net->q_recv);
	chunk_t* chk = pkt->data;

	*src = pkt->src;

	return chk;
}

void* _receiving(void* arg)
{
	network_t* net = arg;
	struct sockaddr_in addr, client;
	unsigned int client_len = sizeof(client);
	int recv_len;
	char buf[1024];

	addr.sin_family = AF_INET;
	addr.sin_port = net->port;
	addr.sin_addr.s_addr = net->src;

	if(bind(net->sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
		logging(ERR, "[NET] Failure bind socket\n");
		return NULL;
	}

	while(1) {
		recv_len = recvfrom(net->sock, buf, 1024, 0, (struct sockaddr*)&client, &client_len);
		if(recv_len) {
			logging(DBG, "[NET] Receive %d-byte packet\n", recv_len);
			_packet_t* pkt = _pkt_create();
			pkt->data = chk_create();
			chk_write(pkt->data, buf, recv_len);
			pkt->src = client.sin_addr.s_addr;
			pkt->dst = net->src;
			enqueue(net->q_recv, pkt);
		}
	}
}

void* _sending(void* arg)
{
	network_t* net = arg;
	struct sockaddr_in addr;
	int recv_len;
	char buf[1024];

	addr.sin_family = AF_INET;
	addr.sin_port = net->port;

	while(1) {
		_packet_t* pkt = dequeue(net->q_send);
		addr.sin_addr.s_addr = pkt->dst;

		sendto(net->sock, pkt->data->ptr, pkt->data->size, 0, (struct sockaddr*)&addr, sizeof(addr));
		logging(DBG, "[NET] Send %d-byte packet\n", pkt->data->size);
		_pkt_free(pkt);
	}
}

void net_running(network_t* net)
{
	pthread_t tid;
	pthread_create(&tid, NULL, _sending, net);
	logging(ALL, "[NET] Start Sending\n");
	pthread_create(&tid, NULL, _receiving, net);
	logging(ALL, "[NET] Start Receiving\n");
}
