/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multiple.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:46:45 by lucmansa          #+#    #+#             */
/*   Updated: 2025/05/26 17:06:26 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	closepipes(t_minishell *minishell, int **pipes)
{
	int	i;

	i = -1;
	while (++i < minishell->nb_cmd)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
}

void setup_pipes(t_minishell *minishell, int ***pipes)
{
    int i;

    *pipes = malloc(sizeof(int*) * (minishell->nb_cmd));
    if (!*pipes)
        return;
    i = 0;
    while (i < minishell->nb_cmd)
    {
        (*pipes)[i] = malloc(sizeof(int) * 2);
        if (pipe((*pipes)[i]) == -1)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        i++;
    }
}

void	redirect_multiple(t_minishell *minishell, int **pipes, int idx)
{
	if (minishell->command_line[idx].redirect.aro || 
		minishell->command_line[idx].redirect.ro)
		redirect_output(minishell, idx);
	if (minishell->command_line[idx].redirect.ri)
		redirect_input(minishell, idx);
	redirect_heredoc(minishell, pipes[idx], idx);
}

void	redirect_close_pipe(t_minishell *minishell, int **pipes, int idx)
{
	if (idx > 0)
		dup2(pipes[idx - 1][0], STDIN_FILENO);
	if (idx < minishell->nb_cmd - 1)
		dup2(pipes[idx][1], STDOUT_FILENO);
}

void	execute_child(t_minishell *minishell, int **pipes, int idx)
{
	char 	*cmdchr;
	int		ret;

	cmdchr = search_command(minishell, idx);
	if (!cmdchr)
		return (faild_schr(minishell, idx, cmdchr));
	redirect_close_pipe(minishell, pipes, idx);
	redirect_multiple(minishell, pipes, idx);
	closepipes(minishell, pipes);
	ret = execute_builtins(cmdchr, minishell, idx);
	if (ret == -1)
		execute_command(cmdchr, minishell, idx);
	exit(ret);
}

void	parent_pipes(t_minishell *minishell, int **pipes, int i)
{
	if (minishell->command_line[i].redirect.heredoc)
		write(pipes[i][1], &minishell->command_line[i].redirect.heredoc,
			ft_strlen(minishell->command_line[i].redirect.heredoc));
}

void wait_all_pid(int *pid, int nb_cmd, int *ret)
{
	int i;

	i = 0;
	while (i < nb_cmd)
	{
		waitpid(pid[i], ret, 0);
		*ret = WEXITSTATUS(*ret) %256;
		i++;
	}
	free(pid);
}

void	cleanup_pipes(int **pipes, int nb_pipes)
{
	int	i;

	if (!pipes)
		return ;
	i = 0;
	while (i < nb_pipes)
	{
		if (pipes[i])
			free(pipes[i]);
		i++;
	}
	free(pipes);
}

void exec_multiple(t_minishell *minishell)
{
    int i;
    int *pid;
    int **pipes;

    setup_pipes(minishell, &pipes);
    pid = malloc(sizeof(int) * minishell->nb_cmd);
	i = 0;
    while (i < minishell->nb_cmd)
    {
        pid[i] = fork();
        if (pid[i] == 0)
            execute_child(minishell, pipes, i);
        else
            parent_pipes(minishell, pipes, i);
        i++;
    }
	closepipes(minishell, pipes);
    wait_all_pid(pid, minishell->nb_cmd, &minishell->rt_val);
    cleanup_pipes(pipes, minishell->nb_cmd);
}
