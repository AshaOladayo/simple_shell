#include "shell.h"

void RunShell(AndyBis_sh *shell)
{
for (;;)
          {
                  if (shell->av[1])
                          exit (98);
                  else if(isatty(STDIN_FILENO))
                          Terinteract(shell);
                  else
                          noTer_interact(shell);
          }
}
