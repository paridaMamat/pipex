/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaimait <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:00:00 by pmaimait          #+#    #+#             */
/*   Updated: 2022/12/13 11:04:55 by pmaimait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	first_cmd(t_pipex *pipex, char **av, char *envp[])
{
	if (pipex->infile == -1)
	{
		close(pipex->outfile);
		close(pipex->end[1]);
		close(pipex->end[0]);
		exit_perror("infile not found\n", 127);
	}
	else
	{
		if (dup2(pipex->infile, 0) == -1)
			exit_perror("dup2 fail\n", 1);
		if (dup2(pipex->end[1], 1) == -1)
			exit_perror("dup2 fail\n", 1);
		if (pipex->outfile != -1)
			close(pipex->outfile);
		close(pipex->infile);
		close(pipex->end[1]);
		close(pipex->end[0]);
		if (pipex->here_doc == 1)
			execute(pipex, av[3], envp);
		else
			execute(pipex, av[2], envp);
	}
}

void	first_command(char **av, t_pipex *pipex, char *envp[])
{
	if (pipe(pipex->end) == -1)
		exit_perror("pipe error\n", 1);
	pipex->pid2[0] = fork();
	if (pipex->pid2[0] == -1)
		exit_perror("fork error\n", 1);
	if (pipex->pid2[0] == 0)
		first_cmd(pipex, av, envp);
	else
	{
		close(pipex->end[1]);
		if (dup2(pipex->end[0], 0) == -1)
			exit_perror("dup2 fail\n", 1);
		close(pipex->end[0]);
		if (pipex->infile != -1)
			close(pipex->infile);
	}
}

void	write_into_pipe(t_pipex *pipex, char *limiter)
{
	char	buf[BUFFER_SIZE + 1];
	int		read_size;

	read_size = 1;
	limiter = ft_strjoin(limiter, "\n");
	buf[0] = 0;
	if (pipe(pipex->end_heredoc) == -1)
		exit_perror("pipe error\n", 1);
	while (read_size != 0)
	{
		ft_putstr_fd("pipe heredoc> ", 1);
		read_size = read(0, buf, BUFFER_SIZE);
		if (read_size < 0)
			exit_perror("ERROR HERE_DOC", 1);
		buf[read_size] = '\0';
		if (ft_strncmp(buf, limiter, ft_strlen(limiter)) == 0)
			break ;
		if (write(pipex->end_heredoc[1], buf, (int)ft_strlen(buf)) == -1)
			exit_perror("error write into pipe", 1);
	}
	free(limiter);
	close(pipex->end_heredoc[1]);
	pipex->infile = pipex->end_heredoc[0];
}

void	open_file(int ac, char **av, t_pipex *pipex)
{
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		if (ac < 6)
			exit_perror("Invalid number of argument\n", 1);
		pipex->here_doc = 1;
		write_into_pipe(pipex, av[2]);
		pipex->outfile = open(av[ac - 1], O_CREAT | O_WRONLY | O_APPEND, 0777);
	}
	else
	{
		pipex->here_doc = 0;
		pipex->infile = open(av[1], O_RDONLY);
		pipex->outfile = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	}
}

int	main(int ac, char **av, char *envp[])
{
	t_pipex	pipex;
	int		i;

	if (ac < 5)
		exit_perror("Invalid number of argument\n", 1);
	open_file(ac, av, &pipex);
	first_command(av, &pipex, envp);
	i = 3;
	if (pipex.here_doc == 1)
		i = 4;
	while (i < ac - 2)
	{
		multiple_pipe(&pipex, av[i], envp);
		i++;
	}
	last_pipe(&pipex, av[ac - 2], envp);
	while (i != -1 || errno != ECHILD)
		i = waitpid(-1, NULL, 0);
	return (0);
}
