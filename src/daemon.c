#include "daemon.h"

daemon_t IKE;

void daemon_create()
{
	IKE.log = log_create();
	IKE.net = net_create();
}
