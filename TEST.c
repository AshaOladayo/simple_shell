#include "shell.h"

void Initialize(AndyBis_sh *shell)
{
	int command;
	char *cmd = NULL;
	cmd = bisgetline(stdin);
	shell->line =  rmComment(cmd);

	shell->arr = BreakIntoTokens(shell->line);
	if(!shell->arr)
                {
                        free(shell->line);
                        exit(0);
                }
	Dothers(shell);
	command = carrycmd(shell,shell->arr[0]);
	if (command != 1)
	{
		shell->stat = command;
		shell->builtn = 1;
		if (shell->arr != NULL)
		{ 
			freeArray(shell->arr);
                        exit(0);
                }
	}
}


int main(int ac, char *av[], char *env[])
{
	AndyBis_sh shell;
	int i;

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
	
	shell.path = PathsList(&shell);

	RunShell(&shell);
	freeArray(shell.av);
	freeArray(shell._envir);
	return (0);
}
