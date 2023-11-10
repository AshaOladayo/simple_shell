#include "shell.h"

/**
 * main - Entry point of the shell program
 * @ac: The number of command-line arguments.
 * @av: An array of strings
 * containing the command-line arguments.
 * @env: An array of strings
 * containing the environment variables.
 * Return: 0 on successful execution.
 */
int main(int ac, char *av[], char *env[])
{
	AndyBis_shInfo shell;
	int i;

	shell.lent = 0;
	shell.interact = 1;
	shell.pid = getpid();
	shell.stat = 0;
	shell.builtn = 0;
	shell.arr = NULL;
	shell.alias = NULL;
	shell.line = NULL;

	(void) env;

	shell.av = (char **)malloc((ac + 1) * sizeof(char *));
	for (i = 0; av[i]; i++)
	{
		shell.av[i] = AB_strdup(av[i]);
	}
	shell.av[i] = NULL;

	for (i = 0; environ[i]; i++)
		;
	shell._envir = (char **)malloc
		((i + 1) * sizeof(char *));
	for (i = 0; environ[i]; i++)
	{
		shell._envir[i] = AB_strdup(environ[i]);
	}
	shell._envir[i] = NULL;
	for (;;)
	{
		if (!isatty(STDIN_FILENO))
			noTer_interact(&shell);
		else if (isatty(STDIN_FILENO))
			Terinteract(&shell);
	}
	freeArray(shell.av);
	freeArray(shell._envir);
	return (0);
}
