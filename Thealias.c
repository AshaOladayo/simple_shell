#include "shell.h"

/**
 * parse_alias - Parse the argument into name and value.
 * @arg: The argument containing the I
 * alias name and value (name=value).
 * @name: Pointer to store the name.
 * @value: Pointer to store the value.
 *
 * Return: 0 on success, -1 on failure.
 */

int parse_alias(char *arg, char **name, char **value) {
	if (arg == NULL || name == NULL || value == NULL) {
		return -1;
	}

	const char *equalSign = strchr(arg, '=');

	if (equalSign == NULL) {
		return -1;
	}

	size_t name_length = equalSign - arg;
	size_t value_length = strlen(equalSign + 1);
	*name = (char *)malloc(name_length + 1);
	*value = (char *)malloc(value_length + 1);

	if (*name == NULL || *value == NULL) {
		if (*name) free(*name);
		if (*value) free(*value);
		return -1;
	}

	strncpy(*name, arg, name_length);
	(*name)[name_length] = '\0';

	strcpy(*value, equalSign + 1);
	return 0;
}


/**
 * add_or_update_alias - Add or
 * update an alias in the alias list.
 * @head: The head of the alias list.
 * @arg: The argument containing the alias name and value.
 *
 * Return: A pointer to the updated alias list.
 */
the_alias *add_or_update_alias(the_alias *head, char *arg)
{
	char *name = NULL, *value = NULL;

	if (parse_alias(arg, &name, &value) == -1)
		return (head);
	the_alias *prevy = NULL, *tempo = head;

	while (tempo != NULL)
	{

		if (strcmp(tempo->name, name) == 0)
		{
			if (strcmp(tempo->value, value) != 0)
			{
				free(tempo->value);
				tempo->value = value;
			}
			else
			{
				free(name);
				free(value);
			}
			return (head);
		}
		prevy = tempo;

		tempo = tempo->next;
	}

	the_alias *new_alias =
		malloc(sizeof(the_alias));

	if (new_alias != NULL)
		new_alias->name = name;
	new_alias->value = value;
	new_alias->next = head;

	return (new_alias);
}



/**
 * print_all_aliases - Prints all aliases in
 * the linked list, one alias per lin
 * @head: Pointer to the alias list.
 */
void print_all_aliases(the_alias *head)
{
	const the_alias *tempo = head;
	int fd = STDOUT_FILENO;

	while (tempo != NULL)
	{
		write(fd, tempo->name, strlen(tempo->name));
		write(fd, "=", 1);
		write(fd, tempo->value, strlen(tempo->value));
		write(fd, "\n", 1);
		tempo = tempo->next;
	}
}


/**
 * get_alias - Get the value of a specific
 * alias and update it if needed.
 * @shell: Pointer to the shell structure.
 * @arg: Name of the alias to get.
 *
 * Return: 0 on success, -1 on failure.
 */
int get_alias(AndyBis_shInfo *shell, char *arg)
{
	char *value = NULL;

	if (!(add_or_update_alias(&the_alias shell *head, arg)))
	{
		return (-1);
	}
	the_alias *tempo = shell->alias;

	while (tempo != NULL)
	{
		if (AB_strcmp(arg, tempo->name)
		{
			value = tempo->value;

			break;
		}
		tempo = tempo->next;

	}

	if (value == NULL)
		return (-1);
	write(STDOUT_FILENO, value, my_strlen(value));
	write(STDOUT_FILENO, "\n", 1);
	return (0);
}

/**
 * aliascommand - Handles the alias
 * command, sets and prints aliases.
 * @shell: Pointer to the shell structure.
 *
 * Return: 0 on success or appropriate error.
 */
int aliascommand(AndyBis_shInfo *shell)
{
	int i, j, check, retu = 0;

	if (!shell->arr[1])
	{
		print_all_aliases(shell->alias);
	}
	else
	{
		for (i = 1; shell->arr[i]; i++)
		{
			check = 0;
			for (j = 0; shell->arr[i][j]; j++)
			{
				if (shell->arr[i][j] == '=')
				{
					check = 1;
					retu = add_or_update_alias(&the_alias shell *head, shell->arr[i]);
					break;
				}
			}
			if (check == 0)
			{
				retu = get_alias(shell, shell->arr[i]);
			}
		}
	}
	return (retu);
}

