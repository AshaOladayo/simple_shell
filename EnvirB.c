#include "shell.h"

/**
 * modEnvir - Adds or modifies an environment variable
 * @shell: Shell data
 *
 * Return: Variable with value
 */
char *modEnvir(AndyBis_sh *shell)
{
	char *str;
	int len1, len2;

	len1 = strlen(shell->arr[1]);
	len2 = strlen(shell->arr[2]);

	str = malloc(sizeof(char) * (len1 + len2 + 2));
	if (!str)
		return (NULL);
	strcpy(str, shell->arr[1]);
	strcat(str, "=");
	strcat(str, shell->arr[2]);
	return (str);
}

/**
 * modDir - Modifies a directory
 * @shell: Pointer to the shell
 * @directory: Directory to set ("old" or "new")
 * @newDirectory: New directory
 *
 * Return: void
 */
void modDir(AndyBis_sh *shell, char *directory, char *newDirectory)
{
freeArray:(shell->arr);
	shell->arr = malloc(sizeof(char *) * 4);
	shell->arr[0] = strdup("setEnvir");

	switch (directory[0])
	{
		case 'o':
			shell->arr[1] = strdup("OLDPWD");
			break;
		case 'n':
			shell->arr[1] = strdup("PWD");
			break;
		default:
			break;
	}
	shell->arr[2] = strdup(newDirectory);
	shell->arr[3] = NULL;

	setEnvir(shell);
}

/**
 * cd_error - Prints an error
 * @shell: Shell data
 * @n: The error number,
 * from cd, set, and unset | 1, 2, 3 respectively
 *
 * Return: 0 or 1
 */
int cd_error(AndyBis_sh *shell, int n)
{
	switch (n)
	{
		case 1:
			write(STDERR_FILENO, shell->av[0], strlen(shell->av[0]));
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, shell->arr[0], strlen(shell->arr[0]));
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, shell->arr[1], strlen(shell->arr[1]));
			write(STDERR_FILENO, ": No such file or directory\n", 28);
			return (1);
		case 2:
			write(STDERR_FILENO, shell->av[0], strlen(shell->av[0]));
			write(STDERR_FILENO, ": Usage: setenv VARIABLE VALUE\n", 31);
			return (1);
		case 3:
			write(STDERR_FILENO, shell->av[0], strlen(shell->av[0]));
			write(STDERR_FILENO, ": Usage: unsetenv VARIABLE\n", 27);
			return (1);
		case 4:
			write(STDOUT_FILENO, shell->arr[1], strlen(shell->arr[1]));
			write(STDOUT_FILENO, ": OLDPWD not set\n", 17);
			return (0);
		default:
			return (1);
	}
}
