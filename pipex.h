/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckojima- <ckojima-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 21:32:07 by ckojima-          #+#    #+#             */
/*   Updated: 2023/08/06 22:39:25 by ckojima-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>

void	check_args(int ac, char *av[], char *envp[]);

void	child1(int *pipefd, int *infile_fd, char *cmd1, char *envp[]);
void	child2(int *pipefd, int *outfile_fd, char *cmd2, char *envp[]);

int		forking(void);
void	open_fds(char *av[], int *files_fds);

void	exec_cmd(char *cmd, char *envp[]);
char	*find_path(char **cmd_wflags, char **envp);
char	*test_path(char **paths, char **cmd_wflags);

int		empty_str(char *str);
void	free_array(char **arr);
void	error(int err);

#endif