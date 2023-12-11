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
int parse_alias(char* arg, char **name,
		char **value) 
{
    if (arg == NULL || name == NULL || 
		    value == NULL)
	    return 0; 

    char *equalSign = strchr(arg, '=');

    if (equalSign == NULL) 
        return -1; 
    
    size_t name_length = equalSign - arg;

    *name = malloc(name_length + 1);

    if (*name == NULL)
        return -1; 
    strncpy(*name, arg, name_length);
    (*name)[name_length] = '\0'; 

    equalSign++;
    // Allocate memory for the value
    *value = strdup(equalSign);

    if (*value == NULL) 
    {
        free(*name);
	free(*value);
        return -1; 
    }
    return 0; // Successfully 
}




/**
 * add_or_update_alias -create,Add or
 * update an alias in the alias list.
 * @head: The head of the alias list.
 * @arg: The argument containing the alias name and value.
 *
 * Return: A pointer to the updated alias list
 */

  int add_or_update_alias(AndyBis_shInfo *shell, the_alias **head, char *arg) {
    char *name = NULL, *value = NULL;
    parse_alias(arg, &name, &value);
    if (parse_alias(arg, &name, &value) != 0) {
    // Handle parse_alias failure
    return -1;
}

    if (name == NULL || value == NULL) {
        // Handle invalid input
        return -1;
    }

    the_alias *temp = *head;
    the_alias *new_alias = malloc(sizeof(the_alias));

    if (new_alias == NULL) {
        // Handle memory allocation failure
        free(name);
        free(value);
        return -1;
    }

    new_alias->name = strdup(name);
    new_alias->value = strdup(value);
    new_alias->next = NULL;

    if (new_alias->name == NULL || new_alias->value == NULL) {
        // Handle memory allocation failure
        free(new_alias->name);
        free(new_alias->value);
        free(new_alias);
        free(name);
        free(value);
        return -1;
    }

    // Update an existing alias if found
    while (temp != NULL) {
        if (strcmp(temp->name, new_alias->name) == 0) {
            // Existing alias found, update its value
            free(temp->value);
            temp->value = strdup(value);
            free(name);
            free(value);
            free(new_alias->name);
            free(new_alias->value);
            free(new_alias);
            return 0;
        }

        if (temp->next == NULL || strcmp(temp->next->name, new_alias->name) == 0) {
            // Add the new alias to the end of the list
            if (temp->next == NULL) {
                temp->next = new_alias;
            } else {
                free(new_alias->name);
                free(new_alias->value);
                free(new_alias);
            }
            free(name);
            free(value);
            return 0;
        }

        temp = temp->next;
    }

    if (*head == NULL) {
        *head = new_alias;
    }

    free(name);
    free(value);
    return 0;
}


int set_alias(AndyBis_shInfo *shell)
{
    if (add_or_update_alias(shell, &shell->alias, shell->arr[1]) == 0)
    {
        // Alias added or updated successfully
        return 0;
    }
    else
    {
        write(STDERR_FILENO, shell->av[0], strlen(shell->av[0]));
        write(STDERR_FILENO, ": Unable to add alias\n", 22);
        return 1;
    }
}





/**
 * print_all_aliases - Prints all aliases in
 * the linked list, one alias per lin
 * @head: Pointer to the alias list
 */
int print_all_aliases(AndyBis_shInfo *shell)
{
    the_alias *current = shell->alias;  // Use the head of the linked list directly

    if (!current)
    {
        write(STDERR_FILENO, shell->av[0], strlen(shell->av[0]));
        write(STDERR_FILENO, ": ", 2);
        write(STDERR_FILENO, shell->arr[1], strlen(shell->arr[1]));
        write(STDERR_FILENO, " not found\n", 11);
        return 1;
    }

    int fd = fileno(stdout);

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

