/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckojima- <ckojima-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 21:38:59 by ckojima-          #+#    #+#             */
/*   Updated: 2023/08/06 22:40:10 by ckojima-         ###   ########.fr       */
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
	{
		ft_putendl_fd("Error: Bad arguments.", 2);
		ft_putendl_fd("Usage: ./pipex <input> <cmd1> <cmd2> <output>", 1);
	}
	if (err == 9)
		ft_putendl_fd("Error: Invalid command.", 2);
	if (err == 10)
		perror("Error (envp)");
	exit(EXIT_FAILURE);
}

void	free_array(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
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
