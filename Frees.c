#include "shell.h"

/**
 *  freeList -for freeing space allocated to list
 *  @head: the start of the list
 *
 *  Return : void
 */
void freeList(the_path *head)
{
	while (head != NULL)
	{
		the_path *tempo = head;

		head = head->next;

		free(tempo->strng);
		free(tempo);
	}
}

/**
 *  freeArray -for freeing space allocated to list
 *  @arr: the array to be freed
 *
 *  Return: void
 */
void freeArray(char **arr)
{
	if (arr != NULL)
	{
		for (int j = 0; arr[j] != NULL; j++)
		{
			free(arr[j]);
		}
		free(arr);
	}
}


/**
 * freeAlias - frees the alias_l linked list
 * @head: pointer to the list
 *
 *  Return: void
 */
void freeAlias(the_alias *head)
{
	the_alias *tempo = head, *sec;

	if (head)
	{
		while (tempo->next)
		{
			sec = tempo;
			tempo = tempo->next;

			free(sec->name);
			free(sec->value);
			free(sec);
		}

		free(tempo->name);
		free(tempo->value);
		free(tempo);
	}
}
