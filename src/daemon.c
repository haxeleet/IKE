#include "daemon.h"
#include <stdlib.h>

daemon_t* daemon;

void daemon_create()
{
	daemon = calloc(1, sizeof(daemon_t));
	daemon->log = log_create();
	daemon->net = net_create();
}
