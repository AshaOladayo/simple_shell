#include "shell.h"

/**
 * domywish - Read and process user
 * input in an interactive manner.
 *
 * Description:
 * This function reads and processes
 * user input in an interactive loop.
 * It handles Ctrl+C signals, reads commands, removes comments and
 *  and tokenizes the input.
 *
 * Return: A dynamically allocated array
 * of strings containing the tokens
 * from the user's input, or (NULL) on error.
 */
char **domywish(AndyBis_shInfo *shell, char *buffer, int **n) {
    char *commnd, *cmd;
    char **tokens = NULL;

    // Allocate memory for commnd
    commnd = malloc(sizeof(char) * BUFSIZE);
    if (commnd == NULL) {
        perror("Error allocating memory for commnd");
        exit(EXIT_FAILURE);
    }

    // Read a line from stdin using bisgetline
    cmd = bisgetline(stdin);

    // Remove comments and trim spaces
    commnd= rmComment(cmd);
    size_t len = strlen(commnd);
    *n = (int *)len;
    

    // Allocate memory for buffer and copy cleanCmd into it
    if (buffer == NULL) {
        perror("Error allocating memory for buffer");
        free(commnd);  // Free the cleaned command
        exit(EXIT_FAILURE);
    }

    // Check if cleanCmd is empty
    if (commnd == NULL || strcmp(commnd, "\n") == 0 || strcmp(commnd, "\t") == 0 || strcmp(commnd, " ") == 0) {
        free(cmd);
        free(commnd);
        free(buffer);
        return NULL;  // Return NULL or handle this case accordingly
    }

    // Break the command into tokens
    tokens = BreakIntoTokens(commnd);

    // Free allocated memory
    free(commnd);
    free(cmd);

    return tokens;
}

/**
 * handlectrlC - Signal handler for SIGINT (Ctrl+C)
 * @signum: The signal number received
 */
void handlectrlC(int signum)
{
	if (signum == SIGINT)
		write(1, "\n", 1);
	exit(0);
}


int ifwhitespace(char *strng) {
    while (*strng) {
        if (!isspace(*strng)) {
            return 0; // Non-whitespace character found
        }
        strng++;
    }
    return 1; // All characters are whitespace
}




/**
 * rmComment - Remove
 * comments from a string.
 * @buffer: Pointer to a string buffer to process.
 *
 * This function removes comments
 * and spaces from the provided string.
 *
 * Return: On success, returns the
 * modified string. On failure, returns (NULL).
 */
char *rmComment(char *buffer) {
    if (buffer == NULL) {
        return NULL;
    }

    // Duplicate the input buffer
    char *buf = strdup(buffer);

    // Check if strdup failed
    if (buf == NULL) {
        return NULL;
    }
// Remove leading whitespaces
    while (isspace((unsigned char)*buf)) {
        buf++;
    }

    // Find the first occurrence of '#' in the duplicated buffer
    char *commentStart = strchr(buf, '#');

    // If '#' is found, replace it and everything after with an empty string
    if (commentStart != NULL) {
        *commentStart = '\0';
    }

    // Find the first occurrence of '\n' in the modified buffer
    char *newline = strchr(buf, '\n');

    // If '\n' is found, replace it with '\0'
    if (newline != NULL) {
        *newline = '\0';
    }

    // No need to free the original buffer, as it is not dynamically allocated

    return buf;
}



/**
 * bisgetline - Read a line from a file stream or stdin.
 * @buffer: A pointer to a buffer to store the read line.
 * @n: A pointer to the size of the buffer.
 * @stream: The file stream to read from.
 *
 * Return: A dynamically allocated
 * buffer containing the read line, or (NULL) on error
 */
char *bisgetline(FILE *stream)
{
        int i = 0;
        ssize_t nread;
        int fd;
        char c = 0, *buffer = malloc(sizeof(char) * BUFSIZE);
        while (c != EOF && c != '\n')
        {
                fd = fileno(stream);
                nread = read(fd, &c, 1);
                if (nread == 0 || nread == -1)
                {
                        free(buffer);
                        if (nread == 0)
                                exit(0);
                        if (nread == -1)
				    perror("Error: ");
                }
                buffer[i] = c;
                if (buffer[0] == '\0')
                {
                        free(buffer);
                        return ("\n");
                }
                if (i + 1 >= BUFSIZE)
                {
                        buffer = realloc(buffer, i + 1);
                        if (buffer == NULL)
                        {
                                free(buffer);
                                return (NULL);
                        }
                }
                i++;
        }
        buffer[i - 1] = '\0';
	if (ifwhitespace(buffer))
	{
		free(buffer);
		return ("\n");
	}
return (buffer);
}

/**
 * BreakIntoTokens - Tokenize a 
 * string using a delimiter.
 * @buffer: The input string to tokenize.
 * @delimiter: The delimiter used for tokenization.
 *
 * Return: An array of tokens or
 * (NULL) on failure. The last element of the
 * array is (NULL).
 */

char **BreakIntoTokens(char *buffer) {
    char *token;
    char *remainder;
    char **arrToks = NULL;
    int i = 0;

    if (buffer == NULL) {
        perror("Input buffer is NULL");
        return NULL;
    }

    // Duplicate the input buffer to avoid modifying the original string
    char *str = strdup(buffer);
    char *rmstr = strdup(buffer);
    if (str == NULL) {
        perror("Error duplicating input buffer");
        return NULL;
    }

    // Allocate memory for the array of pointers
    arrToks = malloc(2 * sizeof(char *));
    if (arrToks == NULL) {
        perror("Error allocating memory for arrToks");
        free(str);
        return NULL;
    }

    // Allocate memory for the first token
    
    token = strtok(str, " ");
    while (token != NULL) {
        // Allocate memory for the current token
        arrToks[i] = strdup(token);
	if (arrToks[i] == NULL) {
        perror("Error allocating memory for the first token");
        freeTokens(arrToks, i + 1);  // Free allocated memory before exit
        free(str);
        return NULL;
    }

    // Allocate memory for the remainder
    remainder = strstr(rmstr, " ");
    remainder += strlen(" ") ;
    arrToks[i + 1] = strdup(remainder);
    if (arrToks[i + 1] == NULL) {
        perror("Error allocating memory for the remainder");
        freeTokens(arrToks, i + 1);  // Free allocated memory before exit
        free(rmstr);
        return NULL;
    }

    free(str);  
    free(rmstr);// Free the duplicated string
    return arrToks;
}
}

// Function to free the allocated memory for the array of pointers
void freeTokens(char **arrToks, int size) {
    for (int i = 0; i < size; i++) {
        free(arrToks[i]);
    }
    free(arrToks);
}

