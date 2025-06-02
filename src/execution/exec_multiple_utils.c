/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multiple_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:46:45 by lucmansa          #+#    #+#             */
/*   Updated: 2025/06/02 18:10:10 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_fail_schr(t_minishell *minishell, int **pipes, int *pid)
{
	free(pid);
	closepipes(minishell, pipes);
	cleanup_pipes(pipes, minishell->nb_cmd);
	exiting(minishell, 0);
}

void	redirect_multiple(t_minishell *minishell, int **pipes, int idx)
{
	if (minishell->command_line[idx].redirect.aro
		|| minishell->command_line[idx].redirect.ro)
		redirect_output(minishell, idx);
	if (minishell->command_line[idx].redirect.ri)
		redirect_input(minishell, idx);
	redirect_heredoc(minishell, pipes[idx], idx);
}

void	execute_child(t_minishell *minishell, int **pipes, int idx, int *pid)
{
	char	*cmdchr;
	int		ret;

	cmdchr = search_command(minishell, idx);
	if (!cmdchr)
		return (faild_schr(minishell, idx, cmdchr),
			exit_fail_schr(minishell, pipes, pid));
	if (idx > 0)
		dup2(pipes[idx - 1][0], STDIN_FILENO);
	if (idx < minishell->nb_cmd - 1)
		dup2(pipes[idx][1], STDOUT_FILENO);
	redirect_multiple(minishell, pipes, idx);
	closepipes(minishell, pipes);
	ret = execute_builtins(cmdchr, minishell, idx);
	if (ret == -1)
		execute_command(cmdchr, minishell, idx);
	exit(ret);
}

void	wait_all_pid(int *pid, int nb_cmd, int *ret)
{
	int	i;

	i = 0;
	while (i < nb_cmd)
	{
		waitpid(pid[i], ret, 0);
		*ret = WEXITSTATUS(*ret) % 256;
		i++;
	}
	free(pid);
}
