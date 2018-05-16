#include "cmd.h"
#include <string.h>

cmd *get_cmd(char *cmd)
{
	for (int i = 0; i < CMD_NUM; i++) {
		if (strcmp(cmd, (cmds + i)->name) == 0)
		{
			return (cmds + i);
		}
	}
	return NULL;
}
