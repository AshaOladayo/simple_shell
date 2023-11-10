#include "shell.h"
/**
 * AB_strdup - Duplicates a string.
 * @str: The string to duplicate.
 *
 * Return: A pointer to the duplicated string, or NULL on failure.
 */
char *AB_strdup(char *str)
{
	if (str == NULL)
	{
		return (NULL);
	}

	size_t lent = strlen(str);
	char *Newstrn = (char *)malloc(lent + 1);

	if (Newstrn == NULL)
	{
		return (NULL);
	}

	strcpy(Newstrn, str);

	return (Newstrn);
}
/**
 * AB_strcmp - Custom string comparison function.
 * @mine: The first string to compare.
 * @yours: The second string to compare.
 *
 * Return:
 *   - 0 if the strings are equal.
 *   - a negative value if str1 is less than str2.
 *   - a positive value if str1 is greater than str2.
 */
int AB_strcmp(char *mine,  char *yours)
{
	while (*mine && *yours)
	{
		switch (*mine - *yours)
		{
			case 0:
				mine++;
				yours++;
				break;
			default:
				return (*mine - *yours);
		}
	}

	return (*mine - *yours);
}

/**
 *  AB_strcpy - Custom string copy function.
 * @des: The destination buffer.
 * @sorc: The source string.
 *
 * Return: A pointer to the destination buffer.
 */
char *AB_strcpy(char *des,  char *sorc)
{
	if (des == NULL || sorc == NULL)
	{
		return (NULL);
	}

	char *origdest = des;

	while ((*des++ = *sorc) != '\0')
	{
		sorc += 1;
	}

	return (origdest);
}


/**
 * AB_Strcat - Custom string concatenation function.
 * @dest: The destination buffer.
 * @src: The source string to append to the destination.
 *
 * Return: A pointer to the destination buffer.
 */

char *AB_Strcat(char *dest, char *src)
{
	if (dest == NULL || src == NULL)
	{
		return (NULL);
	}

	char *origdest = dest;

	while (*dest != '\0')
	{
		dest++;
	}

	while ((*dest = *src) != '\0')
	{
		dest++;
		src++;
	}

	return (origdest);
}


/**
 * AB_strtok - Tokenizes a string
 * @str: String to tokenize
 * @delim: Delimiters to use
 * Return: A token
 */
char *AB_strtok(char *str, char *delim)
{
	static char *s;
	char *ret = NULL;

	if (str != NULL)
	{
		s = str;
	}

	if (s == NULL || *s == '\0')
	{
		return (NULL);
	}

	while (*s != '\0' && strchr(delim, *s) != NULL)
	{
		++s;
	}

	if (*s == '\0')
	{
		return (NULL);
	}

	ret = s;

	while (*s != '\0' && strchr(delim, *s) == NULL)
	{
		++s;
	}

	if (*s != '\0')
	{
		*s = '\0';
		++s;
	}

	return (ret);
}
