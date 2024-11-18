/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halozdem <halozdem@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:37:02 by halozdem          #+#    #+#             */
/*   Updated: 2024/11/18 16:38:23 by halozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_fd(t_jobs *jobs, t_job *job)
{
	int	fd;
	int	indexes[3];
	int	i;

	fd = 1;
	indexes[0] = 0; // i_out
	indexes[1] = 0; // i_app
	indexes[2] = 0; // i_in
	i = -1;
	while (job->redir->files_order && job->redir->files_order[++i])
	{
		fd = process_redirection(jobs, job, indexes, i);
		if (fd == -1)
		{
			g_exit_status = 1;
			return (-1);
		}
		if (i < indexes[2])
			dup2(fd, 0);
		else
			dup2(fd, 1);
		close(fd);
	}
	return (fd);
}

int	process_redirection(t_jobs *jobs, t_job *job, int *indexes, int i)
{
	int		fd;
	char	*file;
	int		len;

	file = job->redir->files_order[i];
	len = ft_strlen(file);
	fd = 1;
	if (job->redir->out_files && !ft_strncmp(file,
			job->redir->out_files[indexes[0]], len)
		&& len == (int)ft_strlen(job->redir->out_files[indexes[0]]))
		fd = open_out_file(jobs, job, job->redir->out_files[indexes[0]++]);
	else if (job->redir->appends && !ft_strncmp(file,
			job->redir->appends[indexes[1]], len)
		&& len == (int)ft_strlen(job->redir->appends[indexes[1]]))
		fd = open_append_file(jobs, job, job->redir->appends[indexes[1]++]);
	else if (job->redir->in_files && !ft_strncmp(file,
			job->redir->in_files[indexes[2]], len)
		&& len == (int)ft_strlen(job->redir->in_files[indexes[2]]))
		fd = open_in_file(jobs, job, job->redir->in_files[indexes[2]++]);
	return (fd);
}

int	open_out_file(t_jobs *jobs, t_job *job, char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file_control(jobs, job, file, fd))
		return (-1);
	job->redir->out_file = fd;
	return (fd);
}

int	open_append_file(t_jobs *jobs, t_job *job, char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (file_control(jobs, job, file, fd))
		return (-1);
	job->redir->append_file = fd;
	return (fd);
}

int	open_in_file(t_jobs *jobs, t_job *job, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (file_control(jobs, job, file, fd))
		return (-1);
	job->redir->in_file = fd;
	return (fd);
}