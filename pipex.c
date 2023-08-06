/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckojima- <ckojima-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 21:34:21 by ckojima-          #+#    #+#             */
/*   Updated: 2023/08/06 22:39:35 by ckojima-         ###   ########.fr       */
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

void	child2(int *pipefd, int *outfile_fd, char *cmd2, char *envp[])
{
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	dup2(outfile_fd[1], STDOUT_FILENO);
	close(outfile_fd[1]);
	// exec command 2  -> EVENTUALLY SEND fds TO CLOSE IN CASE OF ERROR
	exec_cmd(cmd2, envp);
}

void	child1(int *pipefd, int *infile_fd, char *cmd1, char *envp[])
{
	if (dup2(pipefd[1], STDOUT_FILENO) < 0)
		error(5);
	close(pipefd[0]);
	close(pipefd[1]);
	if (dup2(infile_fd[0], STDIN_FILENO) < 0)
		error(5);
	close(infile_fd[0]);
	exec_cmd(cmd1, envp);
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
