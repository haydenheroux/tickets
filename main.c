#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <err.h>

#include "arg.h"
#include "io.h"

#define BUFSIZE 80

int main(int argc, const char** argv) {
	char flags[30];
	size_t chars = get_flags(argc, argv, flags);
	if (chars > 30) {
		fprintf(stderr, "Too many flags!\n");
		return(1);
	}
	char flag = flags[0];
	int ret;
	if (flag == 'd') {
		ret = create_tickets_dir();
	} else if (flag == 'n') {
		ret = write_new_ticket();
	}
	return(ret);
}
