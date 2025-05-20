/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:26:09 by lucmansa          #+#    #+#             */
/*   Updated: 2025/05/20 14:47:09 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_heardoc(t_minishell *minishell, int pipes[2])
{
	if (minishell->command_line[0].redirect.heredoc)
	{
		dup2(pipes[0], STDIN_FILENO);
	}
	close(pipes[0]);
	close(pipes[1]);
	return ;
}

void	default_redirect(t_minishell *minishell, int d_i_o[2], int p[2], int i)
{
	if (i == 0)
	{
		d_i_o[0] = dup(STDIN_FILENO);
		d_i_o[1] = dup(STDOUT_FILENO);
		if (minishell->command_line[0].redirect.aro || 
			minishell->command_line[0].redirect.ro)
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

void	waitandclose(int pipes[2], int	pid, int *ret)
{
	close(pipes[0]);
	close(pipes[1]);
	waitpid(pid, ret, 0);
}

void exec_single(t_minishell *minishell)
{
	char *cmdchr;
	int	pid;
	int	default_[2];
	int	ret;
	int	pipes[2];

	cmdchr = search_command(minishell, 0);
	if (!cmdchr)
		return (faild_schr(minishell, 0, cmdchr));
	pipe(pipes);
	default_redirect(minishell, default_, pipes, 0);
	ret = execute_builtins(cmdchr, minishell, 0);
	if (ret == -1)
	{
		pid = fork();
		if (pid == 0)
		{
			redirect_heardoc(minishell, pipes);
			execute_command(cmdchr, minishell, 0);
		}
		else
			waitandclose(pipes, pid, &ret);
	}
	default_redirect(NULL, default_, NULL, 1);
}
