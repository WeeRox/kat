#include <configr.h>

#include "prompt.h"

int has_token()
{
	int has_token = 1;

	char *home = getenv("HOME");
	char *path = malloc(strlen(home) + strlen("/.katconfig") + 1);
	strcpy(path, home);
	strcat(path, "/.katconfig");

	FILE *config;
	config = fopen(path, "r");
	if (config)
	{
		configr *handle = configr_init();
		configr_parse_stream(handle, config);

		configr_key *key = configr_get_key(handle, "user", "token");
		if (key != NULL)
		{
			has_token = 0;
		}

		configr_free(handle);

		fclose(config);
	}

	return has_token;
}

char *get_user()
{
	char *user = NULL;

	if (has_token() == 0)
	{
		char *home = getenv("HOME");
		char *path = malloc(strlen(home) + strlen("/.katconfig") + 1);
		strcpy(path, home);
		strcat(path, "/.katconfig");

		FILE *config;
		config = fopen(path, "r");
		configr *handle = configr_init();
		configr_parse_stream(handle, config);
		configr_key *key = configr_get_key(handle, "user", "user");
		if (key != NULL)
		{
			user = key->value;
		}

		configr_free(handle);

		fclose(config);
	}
	else
	{
		/* The file doesn't exist */
		user = prompt_text("Email: ");
	}

	return user;
}

char *get_passwd()
{
	char *passwd = NULL;

	if (has_token() == 0)
	{
		char *home = getenv("HOME");
		char *path = malloc(strlen(home) + strlen("/.katconfig") + 1);
		strcpy(path, home);
		strcat(path, "/.katconfig");

		FILE *config;
		config = fopen(strcat(getenv("HOME"), "/.katconfig"), "r");

		configr *handle = configr_init();
		configr_parse_stream(handle, config);

		configr_key *key = configr_get_key(handle, "user", "token");
		passwd = key->value;

		configr_free(handle);

		fclose(config);
	}
	else
	{
		passwd = prompt_passwd("Password: ");
	}

	return passwd;
}
