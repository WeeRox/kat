#include <stdio.h>

int cmd_version(int argc, char **argv)
{
	printf("kat version %s\n", VERSION);
	return 0;
}
