/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaimait <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 14:27:35 by pmaimait          #+#    #+#             */
/*   Updated: 2022/12/12 19:07:29 by pmaimait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex_bonus.h"

void	last_pipe(t_pipex *pipex, char *av, char *envp[])
{
	if (pipe(pipex->end) == -1)
		exit_perror("pipe error\n", 1);
	pipex->pid2[2] = fork();
	if (pipex->pid2[2] == -1)
		exit_perror("fork error\n", 1);
	if (pipex->pid2[2] == 0)
	{
		if (pipex->outfile == -1)
		{
			close(pipex->end[0]);
			close(pipex->end[1]);
			exit_perror("outfile", 1);
		}
		if (dup2(pipex->end[0], 0) == -1)
			exit_perror("dup2 fail\n", 1);
		if (dup2(pipex->outfile, 1) == -1)
			exit_perror("dup2 fail\n", 1);
		close(pipex->end[1]);
		close(pipex->outfile);
		close(pipex->end[0]);
		execute(pipex, av, envp);
	}
	else
	{
		close(pipex->end[1]);
		if (dup2(pipex->end[0], 0) == -1)
			exit_perror("dup2 fail\n", 1);
		close(pipex->end[0]);
		if (pipex->outfile != -1)
			close(pipex->outfile);
	}
}

void	multiple_pipe(t_pipex *pipex, char *av, char *envp[])
{
	if (pipe(pipex->end) == -1)
		exit_perror("pipe error\n", 1);
	pipex->pid2[1] = fork();
	if (pipex->pid2[1] == -1)
		exit_perror("fork error\n", 1);
	if (pipex->pid2[1] == 0)
	{
		if (dup2(pipex->end[1], 1) == -1)
			exit_perror("dup2 fail\n", 1);
		if (pipex->outfile != -1)
			close(pipex->outfile);
		close(pipex->end[0]);
		close(pipex->end[1]);
		execute(pipex, av, envp);
	}
	else
	{
		close(pipex->end[1]);
		if (dup2(pipex->end[0], 0) == -1)
			exit_perror("dup2 fail\n", 1);
		close(pipex->end[0]);
	}
}
