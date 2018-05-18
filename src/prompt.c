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

	struct termios old, new;
	int nread;

	char *buffer;
	int buffer_size;

	/* Turn echoing off and fail if we can’t. */
	if (tcgetattr (fileno (stdin), &old) != 0)
		return -1;
	new = old;
	new.c_lflag &= ~ECHO;
	if (tcsetattr (fileno (stdin), TCSAFLUSH, &new) != 0)
		return -1;

	/* Read the password. */
	nread = getline (&buffer, &buffer_size, stdin);

	/* Restore terminal. */
	(void) tcsetattr (fileno (stdin), TCSAFLUSH, &old);

	return buffer;
}

#else

char *prompt_passwd(char *prompt)
{
	/* TODO: fix a Windows implementation of getpass() */
	return prompt_text(prompt);
}

#endif /* HAVE_GETPASS */
