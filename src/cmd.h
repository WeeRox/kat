#ifndef __KAT_CMD_H
#define __KAT_CMD_H

typedef struct cmd
{
	const char *name;
	int (*fn)(int, char **);
	const char *help;
} cmd;

extern cmd *get_cmd(char *cmd);

extern int cmd_help(int argc, char **argv);

#define CMD_NUM 2

static cmd cmds[] = {
	{ "help", cmd_help,
		"usage: kat help [<command>]\n"
 		"       kat help\n"
	}
};

#endif /* __KAT_CMD_H */
