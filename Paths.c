#include "shell.h"



/**
 * create_node - Create a new the_path
 * node and initialize it with the given string.
 * @str: The string to be stored in the new node.
 * Return: (A pointer to t
 * he newly created node, or NULL on failure).
 */
the_path *create_node(const char *str) {
    the_path *newNode = malloc(sizeof(the_path));
    
    if (!newNode)
        return (NULL);
    
    newNode->path = strdup(str);
    
    if (newNode->path == NULL) {
        free(newNode);
        return (NULL);
    }
    
    newNode->next = NULL;
    
    return (newNode);
}


/**
 * add_node_end - Add a node to
 * the end of a linked list.
 * @head: A pointer to the head of
 * the linked list.
 * @new_node: The node to be
 * added to the end of the list.
 */

void add_node_end(the_path **head, the_path *new_node)
{
    if (!new_node)
    {
        return;
    }

    new_node->next = NULL;

    if (!*head)
    {
        *head = new_node;
    }
    else
    {
        the_path *tempo = *head;
        while (tempo->next)
        {
            tempo = tempo->next;
        }
        tempo->next = new_node;
    }
}


/**
 * path_to_list - Convert environment
 * variables into a linked list
 * of path_l nodes.
 * @shell: A pointer to the sh_data
 * structure containing environment variables.
 * Return: (A pointer to the head
 * of the linked list, or NULL on failure).
 */

the_path *path_to_list(AndyBis_shInfo *shell)
{
    the_path *head = NULL;

    for (int i = 0; shell->_envir[i]; i++)
    {
        char *env = shell->_envir[i];
        char *envCopy = strdup(env);

        if (envCopy == NULL)
        {
            free_path_list(head);
            return NULL;
        }

        char *token = strtok(envCopy, ":");
        while (token != NULL)
        {
            the_path *newNode = create_node(token);

            if (newNode)
            {
                add_node_end(&head, newNode);
            }

            token = strtok(NULL, ":");
        }

        free(envCopy);
    }

    char *pwd = AndyBis_getenv(shell, "PWD");
    the_path *newNode = create_node(pwd);

    if (newNode)
    {
        add_node_end(&head, newNode);
    }

    return head;
}



/**
 * searchPathforfile - Searches for a file in the path linked list.
 * @list: A pointer to the linked list of paths.
 * @file: The file to search for.
 * Return: A pointer to the full path name of the file, or NULL if not found.
 */
char *searchPathforfile(the_path *list, char *file)
{
	char *result = NULL;

	if (list == NULL)
	{
		return (NULL);

		the_path *tempo = list;
		struct stat s;

		while (tempo)
		{
			size_t path_length = strlen(tempo->path) + 1 + strlen(file) + 1;
			char *path = malloc(path_length);

			if (path == NULL)
			{
				freeList(list);
				free(result);
				return (NULL);
			}

			AB_strcpy(path, tempo->path);
			AB_Strcat(path, "/");
			AB_Strcat(path, file);

			if (stat(path, &s) == 0)
			{
				result = AB_strdup(path);
				free(path);
				break;
			}

			free(path);
			tempo = tempo->next;
		}

		return (result);
	}
}
