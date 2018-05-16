#include "cmd.h"
#include <stdio.h>

int cmd_help(int argc, char **argv)
{
	argc--;
	argv++;

	if (argc == 0)
	{
		printf("%s\n", "usage: kat <command>");
	}
	else
	{
		cmd *cmd = get_cmd(*argv);
		printf("%s\n", cmd->help);
	}

	return 0;
}
