#include <stddef.h>
#include <string.h>

size_t get_flags(int argc, const char** argv, char* flagbuf) {
	int flagindex = 0;
	int argindex = 1;
	for (; argindex < argc; argindex++) {
		const char* currentarg = argv[argindex];
		if (currentarg[0] == '-')
		{
			size_t argflagcount = strlen(currentarg) - 1;
			strncpy(&flagbuf[flagindex], &currentarg[1], argflagcount);
			flagindex += argflagcount;
		}
	}
	flagbuf[flagindex + 1] = '\0';
	return flagindex;
}
