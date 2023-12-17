#include "shell.h"
/**
 * prmptAndyBishell - Clear the screen
 * and print a shell prompt.
 */
void prmptAndyBishell(void)
{
	static int initially = 1;

	if (initially)
	{
		const char *clearScreenANSI = "\x1B[2J\x1B[H";

		write(STDOUT_FILENO, clearScreenANSI, 7);
		initially = 0;

	}
	write(STDOUT_FILENO, "VICTOR$ ", 8);

}
