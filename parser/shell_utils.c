/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halozdem <halozdem@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:52:24 by halozdem          #+#    #+#             */
/*   Updated: 2024/11/18 18:53:05 by halozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	initialize_shell(t_mshell *mshell, char **env, t_env **env_list)
{
	g_exit_status = 0;
	mshell->is_exit = 0;
	*env_list = envfunc2(env);
	mshell->jobs = ft_calloc(1, sizeof(t_jobs));
	mshell->jobs->mshell = mshell;
	mshell->jobs->env = *env_list;
}

void	run_shell(t_mshell *mshell)
{
	char	*input;

	while (1)
	{
		reset_job_list(mshell);
		input = readline("minishell> ");
		if (!input)
		{
			free(input);
			break ;
		}
		if (process_user_input(input, mshell) == EXIT_FAILURE)
			continue ;
		executor(mshell);
	}
}

void	cleanup_shell(t_mshell *mshell)
{
	free_jobs_list(mshell->jobs->job_list);
	free_env_list(mshell->jobs->env);
	free(mshell->jobs);
}
