/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaimait <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:07:01 by pmaimait          #+#    #+#             */
/*   Updated: 2022/12/13 11:21:55 by pmaimait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

// for write, read, close, access, pipe, dup, dup2, execve, fork
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>

// for malloc, free, exit
# include <stdlib.h>

//for open
# include <fcntl.h>

// for waitpid
# include <sys/wait.h>

// for strerror
# include <string.h>

// for perror
# include <stdio.h>

typedef struct s_pipex
{
	pid_t	pid[2];
	pid_t	pid2[50];
	int		end[2];
	int		end_heredoc[2];
	int		here_doc;
	int		infile;
	int		outfile;
	char	**path;
	char	*cmd;
	char	**cmd_arg;
}	t_pipex;

//pipex
int		main(int ac, char **av, char **envp);
void	first_child(t_pipex *pipex, char **av, char **envp);
void	second_child(t_pipex *pipex, char **av, char **envp);

//execute
char	**get_path(t_pipex *pipex, char **envp);
char	*get_cmd(char **path, char *cmd);
void	execute(t_pipex *pipex, char *cmd, char **envp);

//utils
void	exit_perror(const char *str, int code);
char	**ft_split(char *s, char c);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		free_array(char **str);
int		print_array(char **str);
#endif
