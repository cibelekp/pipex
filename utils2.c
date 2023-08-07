/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckojima- <ckojima-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 21:38:59 by ckojima-          #+#    #+#             */
/*   Updated: 2023/08/07 22:53:06 by ckojima-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(int err)
{
	if (err == 1)
		perror("Pipe");
	if (err == 2)
		perror("Fork");
	if (err == 3)
		perror("Error (infile)");
	if (err == 4)
		perror("Error (outfile)");
	if (err == 5)
		perror("Error (dup2)");
	if (err == 6)
		ft_putendl_fd("Command not found.", 2);
	if (err == 7)
		perror("Error (execve)");
	if (err == 8)
		ft_putendl_fd("Bad args: ./pipex <input> <cmd1> <cmd2> <output>", 2);
	if (err == 9)
		ft_putendl_fd("Error: Invalid command.", 2);
	if (err == 10)
		perror("Error (envp)");
	if (err == 11)
		perror("Permission denied");
	exit(EXIT_FAILURE);
}

int	empty_str(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] > 32 && str[i] < 127)
			return (0);
	}
	return (1);
}

void	cleanup_fds(int *pipefd, int *files_fds, int *dup_fds)
{
	if (pipefd && pipefd[0] != -1)
		close(pipefd[0]);
	if (pipefd && pipefd[1] != -1)
		close(pipefd[1]);
	if (files_fds && files_fds[0] != -1)
		close(files_fds[0]);
	if (files_fds && files_fds[1] != -1)
		close(files_fds[1]);
	if (dup_fds && dup_fds[0] != -1)
		close(dup_fds[0]);
	if (dup_fds && dup_fds[1] != -1)
		close(dup_fds[1]);
}

void	cleanup_mem(char *str, char **array)
{
	int	i;

	if (str)
		free(str);
	if (array)
	{
		i = -1;
		while (array[++i])
			free(array[i]);
		free(array);
	}
}
