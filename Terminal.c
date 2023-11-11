#include "shell.h"

/**
 * *Terinteract - function that runs when on
 * interactive shell with terminal.
 *
 * @shell: Pointer to the AndyBis_shInfo shell structure
 *
 * This function represents the interactive
 * shell behavior when a terminal is available
 *
 * Return: char *.
 */

char *Terinteract(AndyBis_shInfo *shell)
{
	for (;;)
	{
		int builtnfun;
		char *PATHS;

		prmptAndyBishell();

		shell->arr = domywish();

		if (!shell->arr)
			free(shell->line);
		return (NULL);
		Dothers(shell);

		builtnfun = carrycmd(shell);

		if (builtnfun != 0)
		{
			shell->stat = carrycmd(shell);
			if (shell->arr != NULL)
				freeArray(shell->arr);
			shell->builtn = 1;
			return (NULL);
		}
		PATHS = searchPathforfile(shell->path, shell->arr[0]);

		if (!PATHS)
			continue;
		shell->pid = fork();

		if (shell->pid == 0)
			executeIt(PATHS, shell);
		else
			wait(&shell->stat);
		shell->stat = WEXITSTATUS(shell->stat);

		freeArray(shell->arr);
		free(PATHS);
	}
}


/**
 * executeIt - Execute a command
 * @shell: A pointer to the shell data structure
 * @path: The path to the executable
 */
void executeIt(char *path, AndyBis_shInfo *shell)
{
	shell->stat = execve(path, shell->arr, shell->_envir);
	runChild(shell->stat, shell);
	free(path);
	shell->stat = 0;

	exitShell(shell);
}


/**
 * runChild - Handle child process execution error
 * @stat: The status code of the child process
 * @shell: A pointer to the shell data structure
 */
void runChild(int stat, AndyBis_shInfo *shell)
{
	if (stat == -1)
	{
		write(STDERR_FILENO, shell->av[0], strlen(shell->av[0]));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, shell->arr[0], strlen(shell->arr[0]));
		write(STDERR_FILENO, ": Permission denied\n", 20);
	}
}
