#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <dirent.h>
#include <err.h>
#include <sys/stat.h>

const size_t BUFSIZE = 80;

size_t get_homedir_path(char* result) {
	const char* home = "HOME";
	const char* homepath = getenv(home);
	if (homepath == NULL) {
		err(EXIT_FAILURE, "Error in getting home directory: No environment variable matching HOME was found.");
	}
	size_t chars = strlen(homepath);
	strncpy(result, homepath, chars);
	result[chars] = '\0'; // String has to be zero terminated for "reasons"

	return(chars);
}

size_t get_ticketsdir_path(char* result) {
	char homepath[BUFSIZE];
	size_t chars = get_homedir_path(homepath);
	if (chars >= BUFSIZE) {
		err(EXIT_FAILURE, "Error in getting home directory: Buffer size was too small.");
	}

	chars = snprintf(result, BUFSIZE, "%s/tickets", homepath);
	if (chars >= BUFSIZE) {
		err(EXIT_FAILURE, "Error in getting tickets directory path: Buffer size was too small.");
	} else if (chars < 0) {
		err(EXIT_FAILURE, "Error in getting tickets directory path %s");
	}

	return(chars);
}

int create_tickets_dir() {
	char ticketspath[BUFSIZE];
	get_ticketsdir_path(ticketspath);

	int ret = mkdir(ticketspath, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	if (ret < 0) {
		err(EXIT_FAILURE, "Error in creating tickets directory %s");
	}

	return(ret);
}

int get_next_ticketnum() {
	char ticketspath[BUFSIZE];
	get_ticketsdir_path(ticketspath);
	DIR* ticketsdir = opendir(ticketspath);
	if (ticketsdir == NULL) {
		err(EXIT_FAILURE, "Error in opening tickets directory %s");
	}

	struct dirent *dirfile;
	long currentticketnum = 0;
	while ((dirfile = readdir(ticketsdir)) != NULL) {
		if (dirfile->d_type == DT_REG) {
			char* filename = dirfile->d_name;
			char* stop;
			currentticketnum = strtol(filename, &stop, 10);
		}
	}

	int ret = closedir(ticketsdir);
	if (ret == -1) {
		err(EXIT_FAILURE, "Error in closing tickets directory %s");
	}

	return(currentticketnum + 1);
}
