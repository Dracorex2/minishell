/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multiple_pipes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:44:24 by lucmansa          #+#    #+#             */
/*   Updated: 2025/06/13 16:13:28 by norabino         ###   ########.fr       */
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

void	setup_pipes(t_minishell *minishell, int ***pipes)
{
	int	i;

	*pipes = malloc(sizeof(int *) * (minishell->nb_cmd));
	if (!*pipes)
		return ;
	i = 0;
	while (i < minishell->nb_cmd)
	{
		(*pipes)[i] = malloc(sizeof(int) * 2);
		if (pipe((*pipes)[i]) == -1)
		{
			perror("pipe");
			exit(1);
		}
		i++;
	}
}
