#include "auth.h"
#include "prompt.h"

#include <stdio.h>

int cmd_login(int argc, char **argv)
{
	if (has_token() == 0)
	{
		printf("Already logged in as '%s'\n", get_user());
		if (prompt_yesno("Would you like to logout?", 1))
		{
		}
		else
		{
		}
	}

	return 0;
}
