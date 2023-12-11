#include "shell.h"

/**
 * parse_alias - Parse the argument into name and value.
 * @arg: The argument containing the I
 * alias name and value (name=value).
 * @name: Pointer to store the name.
 * @value: Pointer to store the value.
 *
 * Return: 0 on success, -1 on failure
 */

int parse_alias(char *arg, char **name, char **value) {
    if (arg == NULL || name == NULL || value == NULL)
        return 0;

    char *equalSign = strchr(arg, '=');

    if (equalSign == NULL)
        return -1;

    size_t name_length = equalSign - arg;

    *name = malloc(name_length + 1);

    if (*name == NULL) {
        perror("Error allocating memory for name");
        return -1;
    }

    strncpy(*name, arg, name_length);
    (*name)[name_length] = '\0';

    equalSign++;
    *value = strdup(equalSign);

    if (*value == NULL) {
        perror("Error allocating memory for value");
        free(*name);
        return -1;
    }

    return 0;
}


the_alias *add_or_update_alias(the_alias *head, char *name, char *value) 
{
    the_alias *current = head;
    the_alias *prev = NULL;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) 
	{
            free(current->value);
            current->value = strdup(value);
            return head;
        }
        prev = current;
        current = current->next;
    }

    the_alias *new_alias = malloc(sizeof(the_alias));

    if (new_alias == NULL) 
    {
        perror("Error allocating memory for new_alias");
        return head;  
    }

    new_alias->name = strdup(name);
    new_alias->value = strdup(value);
    new_alias->next = head;  
    return new_alias;  
}



int set_alias(AndyBis_shInfo *shell) {
    char *value, *name = NULL;

    if (parse_alias(shell->arr[1], &name, &value) != 0) {
        // Handle parse_alias failure
        write(STDERR_FILENO, shell->av[0], strlen(shell->av[0]));
        write(STDERR_FILENO, ": Unable to parse alias\n", 24);
        return 1;
    }

    // Update the alias list
    shell->alias = add_or_update_alias(shell->alias, name, value);

    // Free memory used for name and value
    free(name);
    free(value);

    return 0;
}


/**
 * print_all_aliases - Prints all aliases in
 * the linked list, one alias per lin
 * @head: Pointer to the alias list
 */
int print_all_aliases(AndyBis_shInfo *shell)
{
	int fd = fileno(stdout);
	the_alias *current = shell->alias;
	set_alias(shell);
	if (!current)
	{
		write(fd, shell->av[0], strlen(shell->av[0]));
		write(fd, ": ", 2);
		write(fd, " is null\n", 9);
		return 1;
	}
	else
		while (current != NULL)
		{
			write(fd, current->name, strlen(current->name));
			write(fd, "=", 1);
			write(fd, current->value, strlen(current->value));
			write(fd, "\n", 1);
			current = current->next;
		}
	return 0;
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
    char *aliases = NULL;
    the_alias *tempo = shell->alias;
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

    while (tempo != NULL && strcmp(arg, tempo->name) == 0)
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
   
    return 0;
}


/**
 * aliascommand - Handles the alias
 * command, sets and prints aliases.
 * @shell: Pointer to the shell structure.
 *
 * Return: 0 on success or appropriate error.
 */
int aliascommand(AndyBis_shInfo *shell) {
    int i, j, check = 0;
    shell->alias = NULL;
    if (!shell->arr[1]) {
        print_all_aliases(shell);
    } else {
        for (i = 1; shell->arr[i];) {
            check = 0;
            for (j = 0; shell->arr[i][j]; j++) {
                if (shell->arr[i][j] == '=') {
                    check = 1;
                    set_alias(shell);
                    break;
                }
            }
            i++;
        }

        if (check == 0) {
            get_alias(shell, shell->arr[1]);
        }
    }
    return 0;
}

