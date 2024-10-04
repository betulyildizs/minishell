#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	// t_cmd   *cmd;
	char 	*input;
	char	**str;
	char	*ps;
	char	*pe;

	(void)argv;
	if (argc != 1)
	{
		printf("Argument error. \n");
		exit(1);
	}
    while (1)
	{
		input = readline("minishell> ");
		if (!input)
			break;
		add_history(input);
		ps = input;
		pe = ps + ft_strlen(input);
		t_cmd *cmd;
		parser(ps, pe, &cmd);
    }
    // cmd = (t_cmd *)malloc(sizeof(t_cmd));
    // if (!cmd)
        // return (0);
}
