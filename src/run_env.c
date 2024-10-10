#include "minishell.h"

t_env	**lstadd_back(t_env **lst, t_env *new, int n)
{
	t_env	*temp;
	t_env	*temp2;

	temp = *lst;
	if (!*lst)
	{
		*lst = new;
		new->prev = *lst;
	}
	else
	{
		while (temp->next)
		{
			temp2 = temp;
			temp = temp->next;
		}
		temp->next = new;
		new->prev = temp2;
	}
	if (n == 1)
		printf("%s=%s\n", new->key, new->value);
	return (lst);
}

char	*funckey(char	*env, int end)
{
	char	*key;
	key = (char *)malloc(end + 1);
	key[end] = '\0';
	while (end >= 0)
	{
		key[end] = env[end];
		end--;
	}
	return (key);
}

char	*funcval(char	*env, int start)
{
	char	*val;
	int		end;
	int		i;

	i = 0;
	end = start;
	while (env[end])
	{
		end++;
	}
	end--;
	val = (char *)malloc(end - start+ 1);
	while (env[start])
	{
		val[i] = env[start];
		start++;
		i++;
	}
	val[start] = '\0';
	return (val);
}

t_env	**envfunc(char	**env, int n)
{
	int		i;
	int		end;
	t_env	*new;
	t_env	**lst;

	i = 0;
	while (env[i])
	{
		end = 0;
		while ((env[i][end] && env[i][end] != '='))
		{
			end++;
		}
		lst = (t_env **)malloc(sizeof(t_env));
		new = (t_env *)malloc(sizeof(t_env));
		if (!new)
			return (0);
		new->next = NULL;
		new->key = funckey(env[i], end - 1);
		new->value = funcval(env[i], end + 1);
		lstadd_back(lst, new, n);
		i++;
	}
	return (lst);
}
