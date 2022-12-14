/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaimait <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:00:49 by pmaimait          #+#    #+#             */
/*   Updated: 2022/12/13 12:17:26 by pmaimait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include"pipex.h"
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

// for perror, BUFSIZ
# include <stdio.h>

// for errno
# include <errno.h> 

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE BUFSIZ
# endif

//pipex_bonus
int			main(int ac, char **av, char **envp);
void		open_file(int ac, char **av, t_pipex *pipex);
void		first_cmd(t_pipex *pipex, char **av, char *envp[]);
void		write_into_pipe(t_pipex *pipex, char *limiter);
void		first_command(char **av, t_pipex *pipex, char *envp[]);

//multiple_pipe
void		waitpid_all(t_pipex *pipex, int ac);
void		last_pipe(t_pipex *pipex, char *av, char *envp[]);
void		multiple_pipe(t_pipex *pipex, char *av, char *envp[]);

//execute
char		**get_path(t_pipex *pipex, char **envp);
char		*get_cmd(char **path, char *cmd);
void		execute(t_pipex *pipex, char *cmd, char **envp);

//utils
void		exit_perror(const char *str, int code);
char		**ft_split(char *s, char c);
char		*ft_strjoin(char *s1, char *s2);
size_t		ft_strlen(char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			free_table(char **str);
int			print_table(char **str);
void		ft_putstr_fd(char *s, int fd);
char		*joint_and_free(char *str, char *buf);
#endif
