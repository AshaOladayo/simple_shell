#include "shell.h"


/**
 *  Dothers - perform functioni
 *  @shell: pointer to shell structure
 *
 * Return: void
 */

int Dothers(AndyBis_shInfo *shell)
{
	aliascommand(shell);
	expandVar(shell);
	return (0);
}


/**
 * AB_atoi - converts a string 
 * to an integer.
 * @w: input string.
 *
 * Return: integer.
 */

int AB_atoi(char *w)
{
	int resul = 0;
	int sgn = 1;

	if (*w == '-')
	{
		sgn = -1;

		w++;
	}
	while (*w >= '0' && *w <= '9')
	{
		resul = resul * 10 + (*w - '0');

		w++;
	}
	return ((resul * sgn));
}


/**
 * AB_itoa - function converts int to
 * string.
 * @n: type int number.
 *
 * Return: String.
 */
char *AB_itoa(int n)
{
	unsigned int n1;
	int lent = 1;
	int tempo = n;

	while (tempo / 10 != 0)
	{
		lent++;
		tempo /= 10;

	}
	char *buffer = malloc(sizeof(char)
			* (lent + 1));

	if (buffer == 0)
		return (NULL);
	buffer[lent] = '\0';

	if (n < 0)
	{
		n1 = n * -1;
		buffer[0] = '-';

	}
	else
		n1 = n;

	lent--;
	do {
		buffer[lent] = (n1 % 10)
			+ '0';

		n1 = n1 / 10;

		lent--;
	}
	while (n1 > 0);
	return (buffer);
}

/**
 * AndyBis_getenv - Get the value
 * of an environment variable.
 * @shell: A pointer to the shell data structure.
 * @name: The name of the environment
 * variable to retrieve.
 *
 * Return: A pointer to the value of i
 * the environment variable, or NULL if not found.
 */
char *AndyBis_getenv(AndyBis_shInfo *shell, char *name)
{
	if (shell == NULL || name == NULL)
		errno = EINVAL;
	return (NULL);
	char *result = NULL;
	char *envVar;

	for (int i = 0; shell->_envir[i] != NULL; i++)
	{
		envVar = AB_strdup(shell->_envir[i]);

		if (envVar == NULL)
			errno = ENOMEM;

		free(result);
		return (NULL);
		char *envName = AB_strtok(envVar, "=");
		char *envValue = AB_strtok(NULL, "=");

		if (envName != NULL && envValue !=
				NULL && AB_strcmp(envName, name) == 0)
			result = AB_strdup(envValue);
		if (result == NULL)
		{
			errno = ENOMEM;
		}
		break;
	}
	free(envVar);

	if (result == NULL)
		errno = ENOENT;

	return (result);
}
