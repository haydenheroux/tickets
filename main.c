#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <err.h>

#include "arg.h"
#include "io.h"

#define BUFSIZE 80

int main() {
	int num = get_next_ticketnum();
	char ticketspath[BUFSIZE];
	get_ticketsdir_path(ticketspath);

	char nextticketpath[BUFSIZE];
	int chars = snprintf(nextticketpath, BUFSIZE, "%s/%d", ticketspath, num);
	if (chars >= BUFSIZE) {
		err(EXIT_FAILURE, "Error in getting next ticket path: Buffer size was too small.");
	} else if (chars < 0) {
		err(EXIT_FAILURE, "Error in getting next ticket path %s");
	}

	FILE* newticketfile = fopen(nextticketpath, "w");
	if (newticketfile == NULL) {
		err(EXIT_FAILURE, "Error in opening new ticket file %s");
	}

	char username[BUFSIZE];
	int ret = getlogin_r(username, BUFSIZE);
	if (ret != 0) {
		err(EXIT_FAILURE, "Error in getting username %s");
	}

	fprintf(newticketfile, "ticket: %d\ncreator: %s\nstatus: open\n", num, username);

	fclose(newticketfile);
}

int main1(int argc, const char** argv) {
	char flags[30];
	size_t chars = get_flags(argc, argv, flags);
	if (chars > 30) {
		fprintf(stderr, "Too many flags!\n");
		return(1);
	}
	for (int i = 0; i < chars; chars++) {
		char flag = flags[i];
		if (flag == 'd') {
			int ret = create_tickets_dir();
		} else if (flag == 'n') {
			int ret = get_next_ticketnum();
			printf("%d\n", ret);
		}
	}
	return(0);
}
