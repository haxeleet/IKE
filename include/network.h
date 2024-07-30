#ifndef __NETWORK_H__
#define __NETWORK_H__

#include "queue.h"
#include "chunk.h"

#include <stdint.h>

typedef uint32_t ip4_addr;

typedef struct {
  int       sock;
  ip4_addr  src;
  int       port;
  queue_t*  q_send;
  queue_t*  q_recv;
}network_t;

network_t*  net_create(ip4_addr src);
void        net_free(network_t* net);
void        net_send(network_t* net, chunk_t* data, ip4_addr dst);
chunk_t*    net_recv(network_t* net, ip4_addr* src);

void        net_running(network_t* net);

ip4_addr    net_stoa(const char* ipstr);

#endif //__NETWORK_H__
