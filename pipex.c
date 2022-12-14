/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaimait <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 09:05:31 by pmaimait          #+#    #+#             */
/*   Updated: 2022/12/13 11:10:55 by pmaimait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(t_pipex *pipex, char **av, char *envp[])
{
	pipex->infile = open(av[1], O_RDONLY);
	if (pipex->infile == -1)
		write(1, "infile not found\n", 17);
	else
	{
		if (dup2(pipex->infile, 0) == -1)
			exit_perror("dup2 fail\n", 1);
		if (dup2(pipex->end[1], 1) == -1)
			exit_perror("dup2 fail\n", 1);
		close(pipex->end[0]);
		close(pipex->infile);
		close(pipex->end[1]);
		execute(pipex, av[2], envp);
	}
}

void	second_child(t_pipex *pipex, char **av, char **envp)
{
	pipex->outfile = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex->outfile == -1)
		exit_perror("outfile", 1);
	if (dup2(pipex->end[0], 0) == -1)
		exit_perror("dup2 fail\n", 1);
	if (dup2(pipex->outfile, 1) == -1)
		exit_perror("dup2 fail\n", 1);
	close(pipex->end[1]);
	close(pipex->outfile);
	close(pipex->end[0]);
	execute(pipex, av[3], envp);
}

int	main(int ac, char **av, char *envp[])
{
	t_pipex	pipex;

	if (ac != 5)
		exit_perror("Invalid number of argument\n", 1);
	if (pipe(pipex.end) < 0)
		exit_perror("pipe error\n", 1);
	pipex.pid[0] = fork();
	if (pipex.pid[0] == -1)
		exit_perror("fork error\n", 1);
	if (pipex.pid[0] == 0)
		first_child(&pipex, av, envp);
	pipex.pid[1] = fork();
	if (pipex.pid[1] == -1)
		exit_perror("fork error\n", 1);
	if (pipex.pid[1] == 0)
		second_child(&pipex, av, envp);
	close(pipex.end[0]);
	close(pipex.end[1]);
	waitpid(pipex.pid[0], NULL, 0);
	waitpid(pipex.pid[1], NULL, 0);
	return (0);
}
