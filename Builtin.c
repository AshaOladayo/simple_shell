#include "shell.h"

/**
 * carrycmd - Execute a command based
 * on the given input.
 * @shell: A pointer to the shell data
 * structure.
 * Return: An integer representing the
 * success or failure of the command
 * execution.
 */
int carrycmd(AndyBis_sh *shell, char *command)
{
    char *commands[] = {
        "exit", "env", "set", "unset", "cd", "alias"
    };

    int (*f_ptr[6])(AndyBis_sh *shell) = {
        exitShell,
        printEnvir,
        setEnvir,
        unsetEnvir,
        changeDir,
        AliasCommand,
    };

    int numCommands = sizeof(commands) / sizeof(commands[0]);

    for (int i = 0; i < numCommands; i++) {
        if (strcmp(command, commands[i]) == 0) {
            return f_ptr[i](shell);
        }
    }

    return 1;
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

int ifAliasCmd(AndyBis_sh *shell)
{
	D_alias *tempo = shell->alias;
	int i, j, len;
	char *command;

	while (tempo)
	{
		if (AB_strcmp(tempo->name,
					shell->arr[0]) == 0)
		{
			len = AB_strlen(tempo->value);
			command = malloc(sizeof(char *) *
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
