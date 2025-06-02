/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:26:09 by lucmansa          #+#    #+#             */
/*   Updated: 2025/06/02 17:53:03 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	default_redirect(t_minishell *minishell, int d_i_o[2], int p[2], int i)
{
	if (i == 0)
	{
		d_i_o[0] = dup(STDIN_FILENO);
		d_i_o[1] = dup(STDOUT_FILENO);
		if (minishell->command_line[0].redirect.aro
			|| minishell->command_line[0].redirect.ro)
			redirect_output(minishell, 0);
		if (minishell->command_line[0].redirect.ri)
			redirect_input(minishell, 0);
		if (minishell->command_line[0].redirect.heredoc)
			write(p[1], minishell->command_line[0].redirect.heredoc,
				ft_strlen(minishell->command_line[0].redirect.heredoc));
	}
	if (i == 1)
	{
		dup2(d_i_o[0], STDIN_FILENO);
		dup2(d_i_o[1], STDOUT_FILENO);
	}
}

void	waitandclose(int pipes[2], int pid, int *ret)
{
	close(pipes[0]);
	close(pipes[1]);
	waitpid(pid, ret, 0);
	*ret = WEXITSTATUS(*ret) % 256;
}
