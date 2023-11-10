#include "shell.h"

/**
 * noTer_interact - Interactive shell without a terminal
 * @shell: Pointer to the shell data structure.
 *
 * This function handles the non-interactive shell behavior.
 * It searches for the executable in the PATH, and if not found,
 * it handles built-in commands and executes external programs.
 */
void noTer_interact(AndyBis_shInfo *shell)
{
	char *PATHs;

	shell->interact = 0;

	for (;;)
	{
		PATHs = searchPathforfile(shell->path, shell->arr[0]);

		if (!PATHs && shell->builtn == 0)
		{
			exitShell(shell);
		}
		else if (!PATHs && shell->builtn == 1)
		{
			continue;
		}
		shell->builtn = 0;
		shell->pid = fork();

		if (shell->pid == 0)
		{
			executeIt(PATHs, shell);
		}
		else
		{
			wait(&shell->stat);
			shell->stat = WEXITSTATUS(shell->stat);
		}
		freeArray(shell->arr);
		free(PATHs);
	}
}

