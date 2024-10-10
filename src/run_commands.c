#include "minishell.h"

void	run_cmds(char *input, char **env)
{
	if (strncmp(input, "exit", 4) == 0)
		exit(0);
	if (strcmp(input, "env") == 0)
		envfunc(env, 1);
}
