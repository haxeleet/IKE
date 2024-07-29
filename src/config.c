#include "config.h"
#include "log.h"

#include <stdio.h>

configure_t* cfg_create(const char* filename)
{
	config_t cfg;
	config_setting_t *left, *right;
	const char* buf;

	config_init(&cfg);

	if(!config_read_file(&cfg, filename)) {
		logging(ERR, "[CFG] Failure init config(%s:%d - %s)\n", config_error_file(&cfg), config_error_line(&cfg), config_error_text(&cfg));
		config_destroy(&cfg);
		return NULL;
	}

	left = config_lookup(&cfg, "left");
	if(left != NULL) {
		config_setting_lookup_string(left, "ip", &buf);
		printf("%s\n", buf);
	}
}
