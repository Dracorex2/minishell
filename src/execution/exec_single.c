/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:26:09 by lucmansa          #+#    #+#             */
/*   Updated: 2025/05/14 16:27:01 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	redirect_single(t_minishell *minishell)
{
	if (minishell->command_line[0].redirect.aro || 
		minishell->command_line[0].redirect.ro)
		redirect_output(minishell, 0);
	if (minishell->command_line[0].redirect.ri)
		redirect_input(minishell, 0);
}

void exec_single(t_minishell *minishell)
{
	char *cmdchr;
	int	pid;
	int	default_i_o[2];

	cmdchr = search_command(minishell, 0);
	if (!cmdchr)
		faild_schr(minishell, 0, cmdchr);
	default_i_o[0] = dup(STDIN_FILENO);
	default_i_o[1] = dup(STDOUT_FILENO);
	redirect_single(minishell);
	if (!execute_builtins(cmdchr, minishell, 0))
	{
		pid = fork();
		if (pid == 0)
			execute_command(cmdchr, minishell, 0);
		else
			waitpid(pid, NULL, 0);
	}
	dup2(default_i_o[0], STDIN_FILENO);
	dup2(default_i_o[1], STDOUT_FILENO);
}