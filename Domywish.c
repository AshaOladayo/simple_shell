#include "shell.h"

/**
 * domywish - Read and process user
 * input in an interactive manner.
 *
 * Description:
 * This function reads and processes
 * user input in an interactive loop.
 * It handles Ctrl+C signals, reads commands, removes comments and
 * unnecessary whitespace, and tokenizes the input.
 *
 * Return: A dynamically allocated array
 * of strings containing the tokens
 * from the user's input, or (NULL) on error.
 */
char **domywish(void)
{
	signal(SIGINT, handlectrlC);
	size_t n = BUFSIZE;
	char *buffer = NULL;
	char *commnd, *cmd;
	char **arr = NULL;

	while (1)
	{
		/* Read a line of input from the user */
		cmd = bisgetline(&buffer, &n, stdin);
		commnd = rmComment_nd_Space(&cmd);
		if (commnd == NULL)
		{
			free(buffer);
			break;
		}
		if (commnd[0] == '\0' || strcmp(commnd, "\n")
				== 0 || strcmp(commnd, "\t") == 0
				|| strcmp(commnd, " ") == 0)
			continue;
		arr = BreakIntoTokens(commnd, DELIM_T);

		free(buffer);
		free(commnd);
		free(cmd);
	}
	return (arr);
}

/**
 * handlectrlC - Signal handler for SIGINT (Ctrl+C)
 * @signum: The signal number received
 */
void handlectrlC(int signum)
{
	if (signum == SIGINT)
		write(1, "\n", 1);
	char *cmd = NULL;
}

/**
 * bisgetline - Read a line from a file stream or stdin.
 * @lineptr: A pointer to a buffer to store the read line.
 * @n: A pointer to the size of the buffer.
 * @stream: The file stream to read from.
 *
 * Return: A dynamically allocated
 * buffer containing the read line, or (NULL) on error
 */

char *bisgetline(char **lineptr, size_t *n, FILE *stream)
{
	if (lineptr == NULL || n == NULL)
		return (NULL);

	if (*n < BUFSIZE)
		*n = BUFSIZE;

	char *Dbuf = *lineptr ? *lineptr : malloc(*n);

	if (Dbuf == NULL)
		return (NULL);
	size_t countIn = 0; 
	int a;

	while ((a = fgetc(stream)) != EOF && a != '\n')
	{
		if (countIn + 1 >= *n)
			*n *= 2;
		char *newDBuf = realloc(Dbuf, *n);

		if (newDBuf == NULL)
			free(Dbuf);
		return (NULL);
		Dbuf = newDBuf;

		Dbuf[countIn++] = a;
	}
	if (countIn == 0 && a == EOF)
		free(Dbuf);
	return (NULL);
	Dbuf[countIn] = '\0';
	*lineptr = Dbuf;

	return (Dbuf);
}


/**
 * rmComment_nd_Space - Remove
 * comments and spaces from a string.
 * @buffer: Pointer to a string buffer to process.
 *
 * This function removes comments
 * and spaces from the provided string.
 *
 * Return: On success, returns the
 * modified string. On failure, returns (NULL).
 */
char *rmComment_nd_Space(char **buffer)
{
	if (buffer == NULL)
	{
		return (NULL);
	}

	char *buf = AB_strdup(*buffer);

	if (buf == NULL)
	{
		return (NULL);
	}

	for (int i = 0; buf[i] != '\0'; i++)
	{
		if (buf[i] == '#')
		{
			buf[i] = '\n';
			break;
		}
	}

	return (buf);
}

/**
 * BreakIntoTokens - Tokenize a i
 * string using a delimiter.
 * @buffer: The input string to tokenize.
 * @delimiter: The delimiter used for tokenization.
 *
 * Return: An array of tokens or
 * (NULL) on failure. The last element of the
 * array is (NULL).
 */
char **BreakIntoTokens(char *buffer,
		char *delimiter)
{
	if (buffer == NULL || delimiter == NULL)
		return (NULL);
	char *bufdup = strdup(buffer);

	if (bufdup == NULL)
		return (NULL);
	char **tokns = malloc(2 * sizeof(char *));

	if (tokns == NULL)
	{
		free(bufdup);
		return (NULL);
	}
	int use = 0;

	for (char *tokn = strtok(bufdup, delimiter);
			tokn != NULL; tokn = strtok(NULL, delimiter))
	{
		if (strcmp(tokn, "/0") == 0
				|| strcmp(tokn, "/n") == 0)
			free(tokn);
		else
		{
			tokns[use] = strdup(tokn);
			if (tokns[use] == NULL)
			{
				free(bufdup);
				for (int i = 0; i < use; i++)
					free(tokns[i]);
				free(tokns);
				return (NULL);
			}
			use++;
		}
	}
	tokns[use] = NULL;

	free(bufdup);
	return (tokns);
}
