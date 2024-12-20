/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halozdem <halozdem@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:38:32 by halozdem          #+#    #+#             */
/*   Updated: 2024/11/21 14:39:53 by halozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	heredoc(t_jobs *jobs, t_job *job, char state)
{
	int	temp_status;
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (EXIT_FAILURE);
	dup2(pipe_fd[0], 0);
	job->pid = fork();
	if (job->pid == 0)
		child_process(jobs, job, state, pipe_fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	wait_for_child(jobs, job->pid, &temp_status, state);
	return (EXIT_SUCCESS);
}

void	child_process(t_jobs *jobs, t_job *job, char state, int *pipe_fd)
{
	char	*buffer;
	int		i;

	if (state)
		set_signal(HDOC_SF);
	dup2(jobs->mshell->backup_fd[0], 0);
	i = 0;
	while (job->redir->eof[i])
	{
		buffer = readline(">");
		if (!buffer)
		{
			jobs->mshell->doll_quest = 130;
			exit(jobs->mshell->doll_quest);
		}
		handle_eof_condition(job, &i, buffer, pipe_fd);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	exit(0);
}

void	handle_eof_condition(t_job *job, int *i, char *buffer, int *pipe_fd)
{
	int	len1;
	int	len2;

	len1 = ft_strlen(buffer);
	len2 = ft_strlen(job->redir->eof[*i]);
	if (!job->redir->eof[*i + 1] && buffer && !(!ft_strncmp(buffer,
				job->redir->eof[*i], len1) && len1 == len2))
		ft_putendl_fd(buffer, pipe_fd[1]);
	if (!ft_strncmp(buffer, job->redir->eof[*i], len1) && len1 == len2)
		(*i)++;
	free(buffer);
}

void	wait_for_child(t_jobs *jobs, pid_t pid, int *temp_status, char state)
{
	waitpid(pid, temp_status, 0);
	if (state && WIFEXITED(*temp_status))
		jobs->mshell->doll_quest = WEXITSTATUS(*temp_status);
}
