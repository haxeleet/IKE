#include "network.h"
#include <stdlib.h>

typedef struct {
	chunk_t*	data;
	ip4_addr	src;
	ip4_addr	dst;
}_packet_t;

_packet_t*	_pkt_create();
void				_pkt_free(_packet_t** pkt);

network_t* net_create()
{
	network_t* net = calloc(1, sizeof(network_t*));
	net->q_send = que_create();
	net->q_recv = que_create();

	return net;
}

void net_free(network_t** net)
{
	que_free(&((*net)->q_send));
	que_free(&((*net)->q_recv));
	free(*net);
}

_packet_t* _pkt_create()
{
	_packet_t* pkt = calloc(1, sizeof(_packet_t));

	return pkt;
}

void _pkt_free(_packet_t** pkt)
{
	if((*pkt)->data)
		chk_free(&((*pkt)->data));
	free(*pkt);
}

void net_send(network_t* net, chunk_t* data, ip4_addr dst)
{
	_packet_t* pkt = _pkt_create();
	pkt->data = data;
	pkt->dst = dst;
	pkt->src = net->src;

	enqueue(net->q_send, pkt);
}

chunk_t* net_recv(network_t* net, ip4_addr* src)
{
	_packet_t* pkt = dequeue(net->q_recv);
	chunk_t* data = pkt->data;
	*src = pkt->src;

	pkt->data = NULL;
	_pkt_free(&pkt);

	return data;
}
