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
#include <ctype.h>

#define BUFSIZE 1024
#define NEWLINE '\n'
#define DELIM_T " " "\t\n\a\r"

extern char **environ;

/**
* struct PATHs - A linked list of each path in PATH variable
* @path: A variable (i.e., /usr/bin)
* @next: Pointer to the next path in the list
*/
typedef struct path
{
char *strng;
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
} D_alias;

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
D_alias *alias;
the_path *path;
pid_t pid;
int *lent;
} AndyBis_sh;


typedef struct builtin
{
        int (*f_ptr)(AndyBis_sh *);
} builtnfun;

/*AndyBisprompt */
void prmptAndyBishell(void);

/* Builtins */

int carrycmd(AndyBis_sh *, char *);
int ifAliasCmd(AndyBis_sh *);


/* Execution */
void executeIt(char *, AndyBis_sh *);
void runChild(int, AndyBis_sh *);


/* Domywish */
char **domywish(AndyBis_sh *, char*, int **);
void handlectrlC(int);
char *bisgetline(FILE *);
char *rmComment(char *);
char **BreakIntoTokens(char *);
void freeTokens(char **, int); 

/* EnvirA */
int changeDir(AndyBis_sh *);
int exitShell(AndyBis_sh *);
int printEnvir(AndyBis_sh *);
int setEnvir(AndyBis_sh *);
int unsetEnvir(AndyBis_sh *);
/* EnvirB */
char *modEnvir(AndyBis_sh *);
void modDir(AndyBis_sh *, char *, char *);
int cd_error(AndyBis_sh *, int );

/* ExpandVariables */
void expandVar(AndyBis_sh *);
int Dothers(AndyBis_sh *);
/* Frees */
void freeList(the_path *);
void freeArray(char **);
void freeAlias(D_alias *);
/* The execution */
void noTer_interact(AndyBis_sh *);
void Terinteract(AndyBis_sh *);
void Initialize(AndyBis_sh *);
void RunShell(AndyBis_sh *);
/* Paths */
the_path *MakeNode(char *);
the_path *AddNode(the_path **, the_path *, char *);
the_path *PathsList(AndyBis_sh *);
void free_path_list(the_path *head);
char *CheckPath(the_path *, char *);

/* Alias */
int ParseAlias(char *arg, char **name, char **);
D_alias *UpdateAlias(AndyBis_sh *, D_alias *);
int PrintAlias(AndyBis_sh *);
int GetAlias(AndyBis_sh *);
int AliasCommand(AndyBis_sh *);

/* Utilites */
char *AndyBis_getenv(AndyBis_sh *, char *);
char *AB_strdup(char *);
char *AB_itoa(int);
int AB_atoi(char *);
int AB_strcmp( char *,  char *);
char *AB_strcpy(char *,  char *);
char *AB_Strcat(char *,  char *);
char *AB_strtok(char *, char *);
int  AB_strlen(char *);

#endif
