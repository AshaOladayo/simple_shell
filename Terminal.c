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
 * Return: void.
 */

void Terinteract(AndyBis_sh *shell)
{
	int command;
	char *path;
	for(;;)
	{
		prmptAndyBishell();
		Initialize(shell);
		path = CheckPath(shell->path, shell->arr[0]);
		if(!path)
			continue;
		shell->pid = fork();
		if (shell->pid == 0)
		executeIt(path, shell);
		else
		{
			wait(&shell->stat);
			shell->stat = WEXITSTATUS(shell->stat);
		}
		freeArray(shell->arr);
		free(path);
	}
}

/**
 * executeIt - Execute a command
 * @shell: A pointer to the shell data structure
 * @path: The path to the executable
 */
 void executeIt(char *path, AndyBis_sh *shell)
{
	shell->stat = execve(path, shell->arr, shell->_envir);
	runChild(shell->stat, shell);
	free(path);
	shell->stat = 13;

	exitShell(shell);
} 


/**
 * runChild - Handle child process execution error
 * @stat: The status code of the child process
 * @shell: A pointer to the shell data structure
 */
 void runChild(int stat, AndyBis_sh *shell)
{
	if (stat == -1)
	{
		write(STDERR_FILENO, shell->av[0], strlen(shell->av[0]));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, shell->arr[0], strlen(shell->arr[0]));
		write(STDERR_FILENO, ": Permission denied\n", 20);
	}
	return;
}

