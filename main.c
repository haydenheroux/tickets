#include <stdio.h>
#include <string.h>

#include "arg.h"
#include "io.h"


int main(int argc, const char** argv) {
	char flags[30];
	size_t chars = get_flags(argc, argv, flags);
	if (chars > 30) {
		fprintf(stderr, "Too many flags!\n");
		return(1);
	}
	for (int i = 0; i < chars; chars++) {
		if (flags[i] == 'd') {
			int ret = create_tickets_dir();
			return(ret);
		}
	}
	return(0);
}
