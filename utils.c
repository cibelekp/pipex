/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckojima- <ckojima-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 21:42:47 by ckojima-          #+#    #+#             */
/*   Updated: 2023/08/06 22:39:57 by ckojima-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*test_path(char **paths, char **cmd_wflags)
{
	char	*dir;
	char	*cmd_path;
	int		i;

	i = -1;
	while (paths[++i])
	{
		dir = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(dir, cmd_wflags[0]);
		free(dir);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
	}
	free_array(cmd_wflags);
	return (NULL);
}

char	*find_path(char **cmd_wflags, char **envp)
{
	char	**paths;
	char	*cmd_path;
	int		i;

	if (!cmd_wflags[0] || empty_str(cmd_wflags[0]))
		error(6);
	i = -1;
	while (envp[++i] != NULL)
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
			break ;
	}
	paths = ft_split(envp[i] + 5, ':');
	cmd_path = test_path(paths, cmd_wflags);
	free_array(paths);
	if (cmd_path == NULL)
		error(6);
	return (cmd_path);
}

void	exec_cmd(char *cmd, char *envp[])
{
	char	**cmd_wflags;
	char	*cmd_path;

	cmd_wflags = ft_split(cmd, ' ');
	if (access(cmd, F_OK | X_OK) == 0)
		execve(cmd, cmd_wflags, envp);
	cmd_path = find_path(cmd_wflags, envp);
	execve(cmd_path, cmd_wflags, envp);
	free_array(cmd_wflags);
	free(cmd_path);
	error(7);
}

void	open_fds(char *av[], int *files_fds)
{
	files_fds[0] = open(av[1], O_RDONLY);
	if (files_fds[0] < 0)
	{
		close(files_fds[0]);
		error(3);
	}
	files_fds[1] = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (files_fds[1] < 0)
	{
		close(files_fds[1]);
		unlink(av[4]); // double check
		error(4);
	}
}

int	forking(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		error(2);
	return (pid);
}
