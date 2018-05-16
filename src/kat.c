#include <stdio.h>

#include "cmd.h"

int main(int argc, char **argv) {
	/* remove command name */
	argc--;
	argv++;

	if (argc == 0)
	{
		/* print help */
		argc = 1;
		*argv = "help";
	}

	cmd *cmd = get_cmd(*argv);
	if (cmd)
	{
		return cmd->fn(argc, argv);
	}
	else
	{
		fprintf(stderr, "kat: '%s' is not a recognized command, see 'kat --help'\n", *argv);
		return 1;
	}
}
