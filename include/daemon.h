#ifndef __DAEMON_H__
#define __DAEMON_H__

#include "network.h"
#include "log.h"

typedef struct {
  log_t*      log;
  network_t*  net;
}daemon_t;

extern daemon_t* daemon;

void daemon_create();

#endif //__DAEMON_H__
