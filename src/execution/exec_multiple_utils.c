/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multiple_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:46:45 by lucmansa          #+#    #+#             */
/*   Updated: 2025/06/13 16:0:3 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_fail(t_minishell *minishell, int **pipes, int *pid, int nb)
{
	free(pid);
	closepipes(minishell, pipes);
	cleanup_pipes(pipes, minishell->nb_cmd);
	exiting(minishell, nb);
}

static int	redirect_multiple(t_minishell *minishell, int **pipes, int idx)
{
	if (minishell->command_line[idx].redirect.aro
		|| minishell->command_line[idx].redirect.ro)
		if (redirect_output(minishell, idx) < 0)
			return (-1);
	if (minishell->command_line[idx].redirect.ri)
		if (redirect_input(minishell, idx) < 0)
			return (-1);
	redirect_heredoc(minishell, pipes[idx], idx);
	return (1);
}

void	execute_child(t_minishell *minishell, int **pipes, int idx, int *pid)
{
	char	*cmdchr;
	int		ret;

	if (idx > 0)
		dup2(pipes[idx - 1][0], STDIN_FILENO);
	if (idx < minishell->nb_cmd - 1)
		dup2(pipes[idx][1], STDOUT_FILENO);
	if (redirect_multiple(minishell, pipes, idx) < 0)
		exit_fail(minishell, pipes, pid, 1);
	closepipes(minishell, pipes);
	cmdchr = search_command(minishell, idx);
	if (!cmdchr)
		return (faild_schr(minishell, idx, cmdchr, idx),
			exit_fail(minishell, pipes, pid, 127));
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
		printf("tq gradn mere <%d\n", *ret);
		i++;
	}
	free(pid);
}
