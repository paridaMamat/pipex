/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaimait <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 11:20:29 by pmaimait          #+#    #+#             */
/*   Updated: 2022/12/12 19:01:11 by pmaimait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"
#include"pipex_bonus.h"

char	*get_cmd(char **path, char *cmd)
{
	int		i;
	int		fd;
	char	*path_cmd;
	char	*path_cm;

	if (cmd)
	{
		fd = access(cmd, X_OK);
		if (fd != -1)
			return (cmd);
	}
	i = 0;
	while (path[i] && cmd)
	{
		path_cm = ft_strjoin(path[i], "/");
		path_cmd = ft_strjoin(path_cm, cmd);
		free(path_cm);
		fd = access(path_cmd, X_OK);
		if (fd != -1)
			return (path_cmd);
		free(path_cmd);
		i++;
	}
	return (NULL);
}

char	**get_path(t_pipex *pipex, char **envp)
{
	char	*path;

	if (*envp == NULL || envp == NULL || envp[0][0] == 0)
	{
		free(pipex->cmd_arg);
		exit_perror("PATH is empty\n", 127);
	}
	while (ft_strncmp("PATH=", *envp, 5))
		envp++;
	path = *envp + 5;
	return (ft_split(path, ':'));
}

void	execute(t_pipex *pipex, char *cmd, char **envp)
{
	int	result;

	if (*cmd == ' ')
		exit_perror("command not found\n", 127);
	if (!*cmd || !cmd)
		exit_perror("permission denied\n", 127);
	pipex->cmd_arg = ft_split(cmd, ' ');
	if (access(pipex->cmd_arg[0], X_OK) != -1)
	{
		result = execve(pipex->cmd_arg[0], pipex->cmd_arg, NULL);
		free_array(pipex->cmd_arg);
	}
	else
	{
		pipex->path = get_path(pipex, envp);
		pipex->cmd = get_cmd(pipex->path, pipex->cmd_arg[0]);
		free_array(pipex->path);
		if (pipex->cmd != NULL)
			result = execve(pipex->cmd, pipex->cmd_arg, envp);
		else
			result = -1;
		free(pipex->cmd);
		free_array(pipex->cmd_arg);
	}
	if (pipex->cmd && result == -1)
		exit_perror("command not found2\n", 127);
}
