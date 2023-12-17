#include "shell.h"

int ParseAlias(char *arg, char **name, char **value)
{
	size_t name_length, value_length;

	char *equalSign;

	if (arg == NULL)
	{
		*name = NULL;
		*value = NULL;

		return (0);
	}
	equalSign = strchr(arg, '=');

	if (equalSign == NULL)
	{
		*name = NULL;
		*value = NULL;
		write(STDOUT_FILENO, "Error parsing alias", 19);
		return (-1);
	}
	name_length = equalSign - arg;
	*name = malloc(name_length + 1);

	if (*name == NULL)
	{
		free(*name);
		*value = NULL;
		return (0);
	}
	strncpy(*name, arg, name_length);
	(*name)[name_length] = '\0';

	equalSign++;
	*value = strdup(equalSign);

	return (0);
}


D_alias *UpdateAlias(AndyBis_sh *shell, D_alias *head)
{
	char *name, *value = NULL;
	D_alias *current = head;
	D_alias *prev, *new_alias = NULL;

	if (!shell->arr[1])
		return(head);
	else
		ParseAlias(shell->arr[1], &name, &value);
	if (name == NULL || value == NULL)
	{
		if(current == NULL)
			return (NULL);
		else
			return (head);
	}
	while (current != NULL)
	{
		if (strcmp(current->name, name) == 0) 
		{
			free(current->value);
			current->value = strdup(value);
			return (head);
		}
		prev = current;
		current = current->next;
	}
	new_alias = malloc(sizeof(D_alias));

	if (new_alias == NULL) 
	{
		perror("Error allocating memory for new_alias");
		return (head);  
	}
	new_alias->name = strdup(name);
	new_alias->value = strdup(value);
	new_alias->next = head;  
	return (new_alias);  
}

int PrintAlias(AndyBis_sh *shell)
{
	int fd = fileno(stdout);
	D_alias *current = shell->alias;

	if (!current)
	{
		/*        write(fd, "No alias\n", 9);*/
		return(0);
	}

	while (current != NULL)
	{
		write(fd, current->name, strlen(current->name));
		write(fd, "=", 1);
		write(fd, current->value, strlen(current->value));
		write(fd, "\n", 1);
		current = current->next;
	}
	return(0);
}



int GetAlias(AndyBis_sh *shell)
{
	char *aliases = NULL;
	D_alias *tempo = shell->alias;
	int le, n, len, fd;
	fd = fileno(stdout);

	if (!tempo)
	{
		write(STDERR_FILENO, shell->av[0], strlen(shell->av[0]));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, shell->arr[1], strlen(shell->arr[1]));
		write(STDERR_FILENO, " not found\n", 11);
		return (1);
	}
	while (tempo != NULL && strcmp(shell->arr[1], tempo->name) == 0)
	{
		le = strlen(tempo->name);
		n = strlen(tempo->value);
		len = le + n;
		aliases = malloc(sizeof(char) * (len + 2));
		if (aliases == NULL)
			return(1);
		else
		{
			strcpy(aliases, tempo->name);
			strcat(aliases, "=");
			strcat(aliases, tempo->value);
			write(fd, aliases, len + 1);
			write(fd, "\n", 1);
			free(aliases);
		}
		tempo = tempo->next;
	}
	return (0);
}


int AliasCommand(AndyBis_sh *shell)
{
	int i, j, check;
	char *value, *name = NULL;

	if (!shell->arr[1] || shell->arr[1][0] == '\0')
	{
		PrintAlias(shell);
	}
	else
	{
		for (i = 1; shell->arr[i];)
		{
			check = 0;
			for (j = 0; shell->arr[i][j]; j++)
			{
				if (shell->arr[i][j] == '=')
				{
					check = 1;

					shell->alias = UpdateAlias(shell, shell->alias);
					break;
				}
			}
			i++;
		}
		if (check == 0)
			GetAlias(shell);
	}
	return (0);
}
