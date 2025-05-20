/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:29:36 by lucmansa          #+#    #+#             */
/*   Updated: 2025/05/16 18:32:01 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void redirect_output(t_minishell *minishell, int idx)
{
	int fd;

	if (minishell->command_line[idx].redirect.aro)
		fd = open(minishell->command_line[idx].redirect.aro, O_WRONLY | O_CREAT | O_APPEND, 0644);	
	if (minishell->command_line[idx].redirect.ro)	
		fd = open(minishell->command_line[idx].redirect.ro, O_WRONLY | O_CREAT | O_TRUNC, 0644);	
	if (fd == -1)	
		exit(-2);	
	dup2(fd, STDOUT_FILENO);	
	close(fd);
}

void redirect_input(t_minishell *minishell, int idx)
{
	int fd;

	if (minishell->command_line[idx].redirect.ri)
		fd = open(minishell->command_line[idx].redirect.ri, O_RDONLY);
	if (fd == -1)
		exit(-2);
	dup2(fd, STDIN_FILENO);
	close(fd);
}
