#include "shell.h"

/**
 * carrycmd - Execute a command based
 * on the given input.
 * @shell: A pointer to the shell data
 * structure.
 *
 * Return: An integer representing the
 * success or failure of the command
 * execution.
 */

int carrycmd(char **arr, AndyBis_shInfo *shell)
{
	const char *commands[] = {"exit",
		"env", "set", "unset", "cd", "alias"};
	int (*f_ptr[])(AndyBis_shInfo *) ={
		exitShell,
		printEnvir,
		setEnvir,
		unsetEnvir,
		changeDir,
		aliascommand,
		NULL
	};
	int i;

	for (i = 0; i < 6; i++)
	{
		if (strcmp(shell->arr[0], commands[i]) == 0)
		{
			break;
		}
	}

	if (i < 6)
	{
		int result = f_ptr[i](shell);

		return (result);
	}
	else
	{

		return (-1);
	}
}


/**
 * ifAliasCmd - Execute a command
 * based on the given alias input.
 *
 * @shell: A pointer to the shell data
 * structure
 *
 * Return: int
 */

int ifAliasCmd(AndyBis_shInfo *shell)
{
	the_alias *tempo = shell->alias;
	int i, j, len;
	char *command;

	while (tempo)
	{
		if (AB_strcmp(tempo->name,
					shell->arr[0]) == 0)
		{
			len = AB_strlen(tempo->value);
			command = malloc(sizeof(char) *
					(len - 1));

			if (command == NULL)
				return (-1);
			for (i = 1, j = 0; i < len - 1; i++, j++)
				command[j] = tempo->value[i];
			command[j] = '\0';

			free(shell->arr[0]);
			shell->arr[0] = command;
			break;
		}
		tempo = tempo->next;
	}
	return (0);
}
