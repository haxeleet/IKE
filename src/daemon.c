#include "daemon.h"

daemon_t daemon;

void daemon_create()
{
	daemon.log = log_create();
	daemon.net = net_create();
}
