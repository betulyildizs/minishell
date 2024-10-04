#include "../minishell.h"

char	*pass_quotes(char *qs, char *pe, char *quotes)
{
	char a;

	a = *qs;
	if (a != QUOTES)
		return  (qs); //bakıcaz
	while (qs != pe || a != pe)
		qs++;
	*qs = *pe;
	return (pe);
}

int    is_meta(char *str)
{
	if(str == '<')
		return(1);
	else if (str == '>')
		return (1);
	else if (str == '|')
		return (1);
}

int	*get_operator(char	**ps)
{
	char	*str;

	str = *ps;
	while (is_digit(str) == 1)
		str++;
	if (str == '\0')
		return (1);
	if (is_meta(str))
		if (str + 1 && is_meta(str + 1))
			ps = str + 2;
		else
			ps = str + 1;
	return (1);
}

int	get_token(char **ps, char **pe, char **ts, char **te)
{
	if ((!ps || !pe) || (ps == pe))
		return (0); //bakıcaz
	while (((*ps != *pe) && ft_strchr(SPACE, **ps)))
		(*ps)++;
	if (*ps == *pe)
		return (0); //token yok
	*ts = *ps;
	if (get_operator(ps))
		;
	else
		while (!ft_strchr(SEP, **ps))
			if (!pass_quote(ps, *pe, QUOTES))
				(*ps)++;
	*te = *ps;
}
