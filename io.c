#include <stdio.h>
#include <stdlib.h>

#include <err.h>
#include <sys/stat.h>

const size_t BUFSIZE = 80;

int create_tickets_dir() {
	char tickethomepath[BUFSIZE];
	const char *home = "HOME";

	const char* homepath = getenv(home);
	if (homepath == NULL) {
		err(EXIT_FAILURE, "Error in creating tickets directory: No environment variable matching HOME was found.");
	}

	int chars = snprintf(tickethomepath, BUFSIZE, "%s/tickets", homepath);
	if (chars >= BUFSIZE) {
		err(EXIT_FAILURE, "Error in creating tickets directory: Buffer size was too small.");
	} else if (chars < 0) {
		err(EXIT_FAILURE, "Error in creating tickets directory %s");
	}

	int ret = mkdir(tickethomepath, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	if (ret < 0) {
		err(EXIT_FAILURE, "Error in creating tickets directory %s");
	}

	return ret;
}
