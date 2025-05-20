/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multiple.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:46:45 by lucmansa          #+#    #+#             */
/*   Updated: 2025/05/20 15:00:15 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	setup_pipes(t_minishell *minishell, int ***pipes)
{
	int	i;

	*pipes = malloc(sizeof(int *) * (minishell->nb_cmd - 1));
	if (!*pipes)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < minishell->nb_cmd - 1)
	{
		(*pipes)[i] = malloc(sizeof(int) * 2);
		if (!(*pipes)[i])
			exit(EXIT_FAILURE);
		if (pipe((*pipes)[i]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	execute_child(t_minishell *minishell, int **pipes, int idx)
{
	char *cmdchr;

	cmdchr = search_command(minishell, idx);
	if (!cmdchr)
		return (faild_schr(minishell, idx, cmdchr));
	
}

void	close_parent_pipes(int **pipes, int i)
{
	close(pipes[i][0]);
	close(pipes[i][1]);
}

void exec_multiple(t_minishell *minishell)
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
			execute_child(minishell, pipes, i);
		else
			close_parent_pipes(pipes, i);
		i++;
	}
	wait_all_pid(pid, minishell->nb_cmd);
	cleanup_pipes(pipes, minishell->nb_cmd - 1);
	free(pid);
}
