#include "shell.h"

/**
 * changeDir - Change the working directory of the shell
 * @shell: Shell data struct
 *
 * Return: 0 on success, 1 on error
 */

int changeDir(AndyBis_shInfo *shell)
{
	char *Npwd, *Opwd = AndyBis_getenv(shell, "PWD");

	switch (shell->arr[1] ? shell->arr[1][0] : '\0')
	{
		case '\0':
			freeArray(shell->arr);
			shell->arr = malloc(sizeof(char *) * 3);
			shell->arr[0] = strdup("cd");
			shell->arr[1] = AndyBis_getenv(shell, "HOME");
			shell->arr[2] = NULL;
			break;
		case '-':
			free(shell->arr[1]);
			shell->arr[1] = AndyBis_getenv(shell, "OLDPWD");
			if (shell->arr[1] == NULL)
				return (cd_error(shell, 4));
			break;
		default:
			if (chdir(shell->arr[1]) == -1)
				cd_error(shell, 1);
			free(Opwd);
			return (1);
			break;
	}
	Npwd = getcwd(NULL, 1024);
	modDir(shell, "new", Npwd);
	modDir(shell, "old", Opwd);
	free(Npwd);
	free(Opwd);
	return (0);
}



/**
 * printEnvir - Print the environment variables
 * @shell: Shell data
 *
 * Return: 0
 */
int printEnvir(AndyBis_shInfo *shell)
{
	int i;

	for (i = 0; shell->_envir[i]; i++)
	{
		write(STDOUT_FILENO, shell->_envir[i], strlen(shell->_envir[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}
/**
 * setEnvir - Add or modify an environment variable
 * @shell: Shell data
 *
 * Return: 0 on success, 12 if memory allocation fails
 */
int setEnvir(AndyBis_shInfo *shell)
{
	int i, j, m, use, done = 0;
	char **Newenv;

	for (i = 0; shell->_envir[i]; i++)
		;
	if (shell->arr[1] == NULL || shell->arr[2] == NULL)
		return (cd_error(shell, 2));

	Newenv = malloc(sizeof(char *) * (i + 2));
	if (!Newenv)
		return (12);
	for (i = 0; shell->_envir[i]; i++)
	{
		j = 0, use = 0;

		while (shell->_envir[i][j] != '=' && shell->arr[1][j] != '\0')
		{
			if (shell->_envir[i][j] != shell->arr[1][j])
				use = 1;
			j++;
		}
		if (use == 0)
			Newenv[m] = modEnvir(shell);

		m++, done = 1;
		continue;
		Newenv[m] = strdup(shell->_envir[i]);
		m++;
	}
	if (done == 0)
		Newenv[m] = modEnvir(shell);
	Newenv[m + 1] = NULL;

	freeArray(shell->_envir);
	shell->_envir = Newenv;
	return (0);
}


/**
 * unsetEnvir - Delete an environment variable
 * @shell: Shell data
 *
 * Return: 0 on success, 6 if the variable doesn't exist
 */
int unsetEnvir(AndyBis_shInfo *shell) 
{
	int k;
	if (shell->arr[1] == NULL) 
	{
		return write(STDERR_FILENO, "Missing argument\n", 17), 1;
	}

	int done = 0;
	char **newEnv = NULL;

	for (int i = 0, k = 0; shell->_envir[i]; i++) 
	{
		if (!done && !strncmp(shell->
					_envir[i], shell->arr[1], strlen(shell->arr[1]))) 
		{
			done = 1;
			continue;
		}

		newEnv = realloc(newEnv, (k + 1) * sizeof(char *));
		newEnv[k++] = strdup(shell->_envir[i]);
	}

	newEnv = realloc(newEnv, (k + 1) * sizeof(char *));
	newEnv[k] = NULL;

	freeArray(shell->_envir);
	shell->_envir = newEnv;

	 done ? 0 : (write(STDERR_FILENO,
				  "Environment variable does not exist\n", 37), 6);
	return (done);
}
