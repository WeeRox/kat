#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef HAVE_GETPASS
#include <termios.h>
#endif

char *prompt_text(char *prompt)
{
	printf("%s", prompt);

	#define BUFFER_SIZE 1024

	char buffer[BUFFER_SIZE];
	size_t size = 1; /* just a NULL char */
	char *content = malloc(sizeof(char) * BUFFER_SIZE);

	if (content == NULL)
	{
		return NULL;
	}

	content[0] = '\0';

	while (fgets(buffer, BUFFER_SIZE, stdin))
	{
		char *old = content;
		size += strlen(buffer);
		content = realloc(content, size);

		if (content == NULL)
		{
			free(old);
			return NULL;
		}

		if (*(buffer + strlen(buffer) - 1) == '\n')
		{
			/* remove trailing newline */
			*(buffer + strlen(buffer) - 1) = '\0';
			strcat(content, buffer);
			break;
		}

		strcat(content, buffer);
	}

	char *result = malloc(strlen(content) + 1);
	strcpy(result, content);

	free(content);

	return result;
}

#ifdef HAVE_GETPASS

char *prompt_passwd(char *prompt)
{
	printf("%s", prompt);

	struct termios old, new;
	int nread;

	char *buffer = malloc(1);
	size_t buffer_size = 1;

	/* Turn echoing off and fail if we can’t. */
	if (tcgetattr(fileno(stdin), &old) != 0)
		return NULL;

	new = old;
	new.c_lflag &= ~ECHO;

	if (tcsetattr(fileno(stdin), TCSAFLUSH, &new) != 0)
		return NULL;

	/* Read the password. */
	nread = getline(&buffer, &buffer_size, stdin);

	/* Restore terminal. */
	(void) tcsetattr(fileno(stdin), TCSAFLUSH, &old);

	char *result;

	if (*(buffer + nread - 1) == '\n')
	{
		/* remove trailing newline */
		*(buffer + nread - 1) = '\0';
		result = calloc(nread - 1, sizeof(char));
		strcpy(result, buffer);
	}
	printf("\n");

	return result;
}

#else

char *prompt_passwd(char *prompt)
{
	/* TODO: fix a Windows implementation of getpass() */
	return prompt_text(prompt);
}

#endif /* HAVE_GETPASS */

int prompt_yesno(char *prompt, int def)
{
	char *prompt_full = malloc(strlen(prompt) + 1);

	strcpy(prompt_full, prompt);

	if (*(prompt + strlen(prompt) - 1) != ' ')
	{
		prompt_full = realloc(prompt_full, strlen(prompt_full + 1 + 1));
		strcat(prompt_full, " ");
	}

	prompt_full = realloc(prompt_full, strlen(prompt_full) + 6 + 1);

	if (def)
	{
		strcat(prompt_full, "[Y/n] ");
	}
	else
	{
		strcat(prompt_full, "[y/N] ");
	}

	printf("%s", prompt_full);

	char c;
	char *text;

	while (1) {
		text = prompt_text("");
		c = text[0];

		if (strlen(text) == 0)
		{
			return def;
		}
		else if (c == 'Y' || c == 'y')
		{
			return 1;
		}
		else if (c == 'N' || c == 'n')
		{
			return 0;
		}
		else
		{
			/* remove the user input from terminal */
			printf("\x1B[A");
			printf("%s", prompt_full);
			for (size_t i = 0; i < strlen(text); i++) {
				printf(" ");
			}
			for (size_t i = 0; i < strlen(text); i++) {
				printf("\b");
			}
			continue;
		}
	}
}
