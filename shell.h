#ifndef SHELL_H_
#define SHELL_H_

#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stddef.h>

#define BUFSIZE 1024
#define NEWLINE '\n'
#define DELIM_T " \t\n\a\r"

extern char **environ;

/**
* struct PATHs - A linked list of each path in PATH variable
* @path: A variable (i.e., /usr/bin)
* @next: Pointer to the next path in the list
*/
typedef struct path
{
char *path;
struct path *next;
} the_path;

/**
* struct alias - A linked list of all set aliases in the shell
* @alias: The name of the alias
* @value: The value of the alias corresponding to the name
* @next: Pointer to the next alias in aliases
*/
typedef struct alias
{
char *name;
char *value;
struct alias *next;
} the_alias;

/**
* struct shel - Structure containing shell data
* @_envir: The shell environment, 
* copied from the default shell environment
* @ALIASes: Linked list of aliases 
* created in the current shell session
* @arr: An array containing each 
* argument entered into the shell
* @av: Arguments vector
* @builtn: Checks if the last command 
* run was a builtin command or not
* @interact: Returns 1 if it 
* is an interactive shell, or 0 if not
* @length: Length of the line
* @line: The entire line of commands
* @PATHs: Linked list containing the PATH variable
* @pid: Process ID of the current shell
* @stat: Shell status, updated on 
* success/failure of a command
*/
typedef struct shel
{
char **av;
char **arr;
char **_envir;
char *line;
int builtn;
int interact;
int stat;
the_alias *alias;
the_path *path;
pid_t pid;
size_t lent;
} AndyBis_shInfo;

/*AndyBisprompt */
void prmptAndyBishell(void);

/* Builtins */

int carrycmd(AndyBis_shInfo *);
int ifAliasCmd(AndyBis_shInfo *);


/* Execution */
void executeIt(char *, AndyBis_shInfo *);
void runChild(int, AndyBis_shInfo *);


/* Domywish */
char **domywish();
void handlectrlC(int);
char *bisgetline(char **, size_t *, FILE *);
char *rmComment_nd_Space(char **);
char **BreakIntoTokens(char *, char *);

/* EnvirA */
int changeDir(AndyBis_shInfo *);
int exitShell(AndyBis_shInfo *);
int printEnvir(AndyBis_shInfo *);
int setEnvir(AndyBis_shInfo *);
int unsetEnvir(AndyBis_shInfo *);
/* EnvirB */
char *modEnvir(AndyBis_shInfo *);
void modDir(AndyBis_shInfo *, char *, char *);
int cd_error(AndyBis_shInfo *, int );

/* ExpandVariables */
void expandVar(AndyBis_shInfo *);
int Dothers(AndyBis_shInfo *);
/* Frees */
void freeList(the_path *);
void freeArray(char **);
void freeAlias(the_alias *);
/* NoTerminal */
void noTer_interact(AndyBis_shInfo *);
char* Terinteract(AndyBis_shInfo *);
/* Paths */
the_path *create_node(const char *);
void add_node_end(the_path **, the_path *);
the_path *path_to_list(AndyBis_shInfo *);
void free_path_list(the_path *head);
char *searchPathforfile(the_path *, char *);

/* Alias */
int parse_alias(char *arg, char **name, char **);
the_alias *add_or_update_alias(the_alias *, char *);
void print_all_aliases(the_alias *);
int get_alias(AndyBis_shInfo *, char *);
int aliascommand(AndyBis_shInfo *);


/* Utilites */
char *AndyBis_getenv(AndyBis_shInfo *, char *);
char *AB_strdup(char *);
char *AB_itoa(int);
int AB_atoi(char *);
int AB_strcmp( char *,  char *);
char *AB_strcpy(char *,  char *);
char *AB_Strcat(char *,  char *);
char *AB_strtok(char *, char *);
int  AB_strlen(char *);

#endif
