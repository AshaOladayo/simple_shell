#include "shell.h"


/**
 * expandVar - expands a variable to its corresponding value
 * @shell: pointer to shell structure
 *
 * Return: void
 */

void expandVar(AndyBis_sh *shell)
{
    char *str, *value;

    for (int i = 0; shell->arr[i]; i++)
    {
        if (AB_strcmp(shell->arr[i], "$$") == 0) 
	{
            free(shell->arr[i]);
            shell->arr[i] = AB_strdup(AB_itoa(shell->pid));
        } else if (AB_strcmp(shell->arr[i], "$?") == 0) {
            free(shell->arr[i]);
            shell->arr[i] = AB_strdup(AB_itoa(shell->stat));
        } else if (shell->arr[i][0] == '$') {
            char *varName = shell->arr[i] + 1;
            value = AndyBis_getenv(shell, varName);
            if (value != NULL) {
                free(shell->arr[i]);
                shell->arr[i] = AB_strdup(value);
                free(value);
            }
        }
    }
}


int AB_strlen(char *str) 
{
    int lent, count;
    for (lent = 0; str[lent] != '\0'; lent++)
    {
	    count++;
    }
    return (count);
}
