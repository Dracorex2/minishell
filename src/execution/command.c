/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:40:28 by lucmansa          #+#    #+#             */
/*   Updated: 2025/06/24 15:40:28 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	faild_schr(t_minishell *minishell, int i, char *schr, int idx)
{
	if (minishell->command_line[idx].args[0])
	{
		write(2, "minishell: Command not found: ", 30);
		write(2, minishell->command_line[i].args[0],
			ft_strlen(minishell->command_line[i].args[0]));
		write(2, "\n", 1);
	}
	free(schr);
}

char	*find_in_path(t_minishell *minishell, int idx)
{
	char	**path;
	int		i;
	char	*path_tmp;
	char	*cmd;

	path = ft_split(ft_getenv(minishell->env, "PATH"), ':');
	i = -1;
	while (path && path[++i])
	{
		path_tmp = ft_strjoin(path[i], "/");
		cmd = ft_strjoin(path_tmp, minishell->command_line[idx].args[0]);
		free(path_tmp);
		if (access(cmd, X_OK) == 0)
			return (ft_free_split(path), cmd);
		free(cmd);
	}
	ft_free_split(path);
	return (NULL);
}

char	*search_command(t_minishell *minishell, int idx)
{
	if (!minishell->command_line[idx].args[0]
		|| !minishell->command_line[idx].args[0][0])
		return (NULL);
	if (ft_strchr(minishell->command_line[idx].args[0], '/'))
	{
		if (access(minishell->command_line[idx].args[0], X_OK) == 0)
			return (ft_strdup(minishell->command_line[idx].args[0]));
		return (NULL);
	}
	if (is_builtin(minishell, idx))
		return (minishell->command_line[idx].args[0]);
	if (minishell->env && ft_getenv(minishell->env, "PATH"))
		return (find_in_path(minishell, idx));
	return (NULL);
}

void	execute_command(char *cmd, t_minishell *minishell, int idx)
{
	execve(cmd, (char *const *)minishell->command_line[idx].args,
		minishell->env);
	free(cmd);
	exit (0);
}
