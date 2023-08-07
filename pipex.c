/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckojima- <ckojima-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 21:34:21 by ckojima-          #+#    #+#             */
/*   Updated: 2023/08/07 20:57:01 by ckojima-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_args(int ac, char *av[], char *envp[])
{
	if (ac != 5)
		error(8);
	if (av[2] == NULL || av[3] == NULL)
		error(9);
	if (envp == NULL)
		error(10);
}

void	child2(int *pipefd, int *files_fds, char *cmd2, char *envp[])
{
	int	dup_fds[2];

	dup_fds[0] = dup2(pipefd[0], STDIN_FILENO);
	if (dup_fds[0] < 0)
		error(5);
	close(pipefd[0]);
	close(pipefd[1]);
	dup_fds[1] = dup2(files_fds[1], STDOUT_FILENO);
	if (dup_fds[1] < 0)
		error(5);
	close(files_fds[1]);
	if (exec_cmd(cmd2, envp) == -1) //
	{
		cleanup_fds(pipefd, files_fds, dup_fds);
		// error(11); //or no message, just exit otherwise double message
		exit(EXIT_FAILURE);
	}
}

void	child1(int *pipefd, int *files_fds, char *cmd1, char *envp[])
{
	int	dup_fds[2];

	dup_fds[0] = dup2(pipefd[1], STDOUT_FILENO);
	if (dup_fds[0] < 0)
		error(5);
	close(pipefd[0]);
	close(pipefd[1]);
	dup_fds[1] = dup2(files_fds[0], STDIN_FILENO);
	if (dup_fds[1] < 0)
		error(5);
	close(files_fds[0]);
	// exec_cmd(cmd1, envp);
	if (exec_cmd(cmd1, envp) == -1) //
	{
		cleanup_fds(pipefd, files_fds, dup_fds);
		// error(11); //or no message, just exit otherwise double message
		exit(EXIT_FAILURE);
	}
}

int	main(int ac, char *av[], char *envp[])
{
	int	pid1;
	int	pid2;
	int	files_fds[2];
	int	pipefd[2];

	check_args(ac, av, envp);
	if (pipe(pipefd) == -1)
		error(1);
	open_fds(av, files_fds);
	pid1 = forking();
	if (pid1 == 0)
		child1(pipefd, files_fds, av[2], envp);
	pid2 = forking();
	if (pid2 == 0)
		child2(pipefd, files_fds, av[3], envp);
	close(pipefd[0]);
	close(pipefd[1]);
	close(files_fds[0]);
	close(files_fds[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
