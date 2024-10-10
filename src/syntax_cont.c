#include "minishell.h"

int	syntax_cont(char *input)
{
	int i;

	i = 0;
	printf("\nSYNTAX CONT\n");
	while (input[i] == ' ' || input[i] == '\t' || input[i] == '\v'
		|| input[i] == '\f' || input[i] == '\r')
		i++;
	if (input[i] == '\0')
		return (0);
	
	return (0);
}
