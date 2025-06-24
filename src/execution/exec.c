/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:18:08 by lucmansa          #+#    #+#             */
/*   Updated: 2025/06/23 18:45:51 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_executing(int val)
{
	static int	executing = 0;

	if (val == 1)
		executing = 1;
	else if (val == 2)
		executing = 0;
	return (executing);
}

static void	exec_multiple(t_minishell *minishell)
{
	int	i;
	int	*pid;
	int	**pipes;

	setup_pipes(minishell, &pipes);
	pid = malloc(sizeof(int) * minishell->nb_cmd);
	i = 0;
	while (i < minishell->nb_cmd)
	{
		pid[i] = fork();
		if (pid[i] == 0)
			execute_child(minishell, pipes, i, pid);
		else
			if (minishell->command_line[i].redirect.heredoc)
				write(pipes[i][1],
					&minishell->command_line[i].redirect.heredoc,
					ft_strlen(minishell->command_line[i].redirect.heredoc));
		i++;
	}
	closepipes(minishell, pipes);
	wait_all_pid(pid, minishell->nb_cmd, &minishell->rt_val);
	cleanup_pipes(pipes, minishell->nb_cmd);
}

static int	exec_single(t_minishell *minishell)
{
	char	*cmdchr;
	int		default_[2];
	int		ret;
	int		pipes[2];

	pipe(pipes);
	if (default_redirect(minishell, default_, pipes, 0) < 0)
		return (default_redirect(NULL, default_, NULL, 1));
	cmdchr = search_command(minishell, 0);
	if (!cmdchr)
		return (default_redirect(NULL, default_, NULL, 1),
			faild_schr(minishell, 0, cmdchr, 0), minishell->rt_val = 127, 0);
	ret = execute_builtins(cmdchr, minishell, 0);
	minishell->rt_val = ret;
	if (ret == -1)
	{
		single_fork(minishell, cmdchr, pipes);
		free(cmdchr);
	}
	return (default_redirect(NULL, default_, NULL, 1), 0);
}

void	exec_cmd(t_minishell *minishell)
{
	is_executing(1);
	if (minishell->nb_cmd == 1)
		exec_single(minishell);
	else
		exec_multiple(minishell);
	is_executing(2);
}
