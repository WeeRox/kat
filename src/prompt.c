#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

char *prompt_passwd(char *prompt)
{
	return getpass(prompt);
}
