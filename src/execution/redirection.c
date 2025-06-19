/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:29:36 by lucmansa          #+#    #+#             */
/*   Updated: 2025/06/16 17:25:16 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_heredoc(t_minishell *minishell, int pipes[2], int ixd)
{
	if (minishell->command_line[ixd].redirect.heredoc)
	{
		dup2(pipes[0], STDIN_FILENO);
		close(pipes[0]);
		close(pipes[1]);
	}
	return ;
}

int	redirect_output(t_minishell *minishell, int idx)
{
	int	fd;

	fd = 0;
	if (minishell->command_line[idx].redirect.aro)
	{
		fd = open(minishell->command_line[idx].redirect.aro,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			perror(minishell->command_line[idx].redirect.aro);
	}
	if (minishell->command_line[idx].redirect.ro)
	{
		fd = open(minishell->command_line[idx].redirect.ro,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			perror(minishell->command_line[idx].redirect.ro);
	}
	if (fd == -1)
		return (-1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

int	redirect_input(t_minishell *minishell, int idx)
{
	int	fd;

	fd = open(minishell->command_line[idx].redirect.ri, O_RDONLY);
	if (fd == -1)
	{
		perror(minishell->command_line[idx].redirect.ri);
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (1);
}
