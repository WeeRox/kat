#include <stdio.h>
#include <string.h>

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
	else if (strcmp(*argv, "--help") == 0 || strcmp(*argv, "--version") == 0)
	{
		/* remove the dashes */
		*argv += 2;
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
