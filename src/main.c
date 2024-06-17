#include <stdio.h>

#include "daemon.h"

static daemon_t daemon;

void init() {
	daemon.net = net_create();
}

int main() {
	printf("Hello world!!!\n");

	while(1);

	return 0;
}
