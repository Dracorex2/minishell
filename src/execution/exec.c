/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:18:08 by lucmansa          #+#    #+#             */
/*   Updated: 2025/06/02 17:57:36 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_multiple(t_minishell *minishell)
{
	int	i;
	int	*pid;
	int	**pipes;

	printf("nb_command : %i\n", minishell->nb_cmd);
	setup_pipes(minishell, &pipes);
	pid = malloc(sizeof(int) * minishell->nb_cmd);
	i = 0;
	while (i < minishell->nb_cmd)
	{
		pid[i] = fork();
		if (pid[i] == 0)
			execute_child(minishell, pipes, i, pid);
		else
			parent_pipes(minishell, pipes, i);
		i++;
	}
	closepipes(minishell, pipes);
	wait_all_pid(pid, minishell->nb_cmd, &minishell->rt_val);
	cleanup_pipes(pipes, minishell->nb_cmd);
}

void	exec_single(t_minishell *minishell)
{
	char	*cmdchr;
	int		pid;
	int		default_[2];
	int		ret;
	int		pipes[2];

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
			redirect_heredoc(minishell, pipes, 0);
			execute_command(cmdchr, minishell, 0);
		}
		else
			waitandclose(pipes, pid, &minishell->rt_val);
	}
	default_redirect(NULL, default_, NULL, 1);
	free(cmdchr);
}

void	exec_cmd(t_minishell *minishell)
{
	if (minishell->nb_cmd == 1)
		exec_single(minishell);
	else
		exec_multiple(minishell);
}
