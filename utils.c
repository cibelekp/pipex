/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckojima- <ckojima-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 21:42:47 by ckojima-          #+#    #+#             */
/*   Updated: 2023/08/07 20:52:20 by ckojima-         ###   ########.fr       */
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
	// free_array(cmd_wflags);
	cleanup_mem(NULL, cmd_wflags);
	return (NULL);
}

char	*find_path(char **cmd_wflags, char **envp)
{
	char	**paths;
	char	*cmd_path;
	int		i;

	if (!cmd_wflags[0] || empty_str(cmd_wflags[0]))
	{
		// error(6); // err msg but no exit
		ft_putendl_fd("Command not found. Permission denied.", 2);
		return (NULL); //close_and_free
	}
	i = -1;
	while (envp[++i] != NULL)
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
			break ;
	}
	paths = ft_split(envp[i] + 5, ':');
	cmd_path = test_path(paths, cmd_wflags);
	// free_array(paths);
	cleanup_mem(NULL, paths);
	if (cmd_path == NULL)
	{
		// error(6); // err msg but no exit
		ft_putendl_fd("Command not found. Permission denied.", 2);
		return (NULL); //close_and_free
	}
	return (cmd_path);
}

int	exec_cmd(char *cmd, char *envp[])
{
	char	**cmd_wflags;
	char	*cmd_path;

	cmd_wflags = ft_split(cmd, ' ');
	if (access(cmd, F_OK | X_OK) == 0)
		execve(cmd, cmd_wflags, envp);
	cmd_path = find_path(cmd_wflags, envp);
	if (cmd_path == NULL)
	{
		cleanup_mem(cmd_path, cmd_wflags);
		return (-1); //close_fds
	}
	execve(cmd_path, cmd_wflags, envp);
	cleanup_mem(cmd_path, cmd_wflags);
	// error(7); // err msg but no exit
	perror("Error (execve)");
	return (-1); //close_fds
}

void	open_fds(char *av[], int *files_fds)
{
	files_fds[0] = open(av[1], O_RDONLY);
	if (files_fds[0] < 0)
		error(3);
	files_fds[1] = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (files_fds[1] < 0)
	{
		close(files_fds[0]);
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
