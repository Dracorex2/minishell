/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:40:28 by lucmansa          #+#    #+#             */
/*   Updated: 2025/05/27 18:07:20 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	faild_schr(t_minishell *minishell, int i, char *schr)
{
		printf("Command not found: %s\n", minishell->command_line[i].args[0]);
		free(schr);
}

char	*search_command(t_minishell *minishell, int idx) 
{
	char	**path;
	int		i;
	char	*cmd;
	char	*path_tmp;

	if (ft_strchr(minishell->command_line[idx].args[0], '/'))
	{
		if (access(minishell->command_line[idx].args[0], X_OK) == 0)
			return (minishell->command_line[idx].args[0]);
		return(NULL);
	}
	if (is_builtin(minishell, idx))
		return (minishell->command_line[idx].args[0]);
	if (minishell->env[0])
	{
		path = ft_split(ft_getenv(minishell->env, "PATH"), ':');
		i = -1;
		while (path[++i])
		{
			path_tmp = ft_strjoin(path[i], "/");
			cmd = ft_strjoin(path_tmp, minishell->command_line[idx].args[0]);
			free(path_tmp);
			if (access(cmd, X_OK) == 0)
				return (ft_free_split(path), cmd);
			free(cmd);
		}
		ft_free_split(path);
	}
	return (NULL);
}

void	execute_command(char *cmd, t_minishell *minishell, int idx)
{
	if (execve(cmd,
		(char * const*)minishell->command_line[idx].args,
		minishell->env) == -1)
		exit (0);
}
