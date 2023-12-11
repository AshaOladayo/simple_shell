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

void Terinteract(AndyBis_shInfo *shell)
{
	for (;;)
	{
		/*builtnfun func;
		char *PATHS;*/
		char **buffer;
		size_t *n;
		char *cmd;
		char **name;
		char **value;
		char **arrIterator;
		/*char  *retu;
		the_alias *ret;*/

		prmptAndyBishell();
		cmd = bisgetline(stdin);
		shell->line =  rmComment(cmd);
                printf("%s\n", shell->line);
		shell->arr = BreakIntoTokens(shell->line);
		
		arrIterator = shell->arr;
		while (*arrIterator != NULL)
		{
			printf("%s\n", *arrIterator);
			arrIterator++;
		}

	        /*if (!shell->arr)
                {
                        free(shell->line);
                        free(cmd);
                        freeArray(shell->arr);
                }*/
           /*    carrycmd(shell);*/
		arrIterator = shell->arr;
		/*add_or_update_alias(shell, &shell->alias, shell->av[1]);*/


    // Print the linked list starting from the first node
   /* print_all_aliases(shell, shell->alias);*/

	       aliascommand(shell);
               /* int result = func.f_ptr(shell);*/ 
	}
}
	       
		/*if (!shell->arr)
		{
			free(shell->line);
			free(cmd);
			freeArray(shell->arr);

		}*/
		/*func.f_ptr = carrycmd;*/
		/*int result = func.f_ptr(shell);*/
		/*if (carrycmd(shell) != 0)
		{
                        shell->stat = carrycmd(shell);
                        if (shell->arr != NULL)
                                freeArray(shell->arr);
                        shell->builtn = 1;
		}*/
	
		/*Dothers(shell);
		ifAliasCmd(shell);*/

                	
	/*return (NULL);} */
		
			/* return (NULL); 
		
		/*PATHS = searchPathforfile(shell->path, shell->arr[0]); */

	/*	if (!PATHS)
			continue; */
		/*shell->pid = fork();

		if (shell->pid == 0)
			executeIt(PATHS, shell);
		else
			wait(&shell->stat);
		shell->stat = WEXITSTATUS(shell->stat);
		

		freeArray(shell->arr);
		free(PATHS);
	}
}
*/





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
	shell->stat = 13;

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
