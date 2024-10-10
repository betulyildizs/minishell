#include "minishell.h"

int main(int ac, char **av, char **env)
{
	char 	*input;

	(void)av;
	if (ac != 1)
	{
		printf("Argument error. \n");
		return (0);
		//exit(1);
	}
    while (1)
	{
		input = readline("minishell> ");
		printf("%s\n", input);
		if (!input)
			break;
		add_history(input);
		syntax_cont(input);
		run_cmds(input, env);
    }
	return (0);
}
