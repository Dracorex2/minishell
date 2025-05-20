/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:40:28 by lucmansa          #+#    #+#             */
/*   Updated: 2025/05/20 15:26:01 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	faild_schr(t_minishell *minishell, int i, char *schr)
{
		printf("Command not found: %s\n", minishell->command_line[i].cmd);
		free(schr);
}

char	*search_command(t_minishell *minishell, int nb_cmd) 
{
	char	**path;
	int		i;
	char	*cmd;

	if (ft_strchr(minishell->command_line[nb_cmd].cmd, '/') && access(minishell->command_line[nb_cmd].cmd, X_OK) == 0)
		return (minishell->command_line[nb_cmd].cmd);
	if (is_builtin(minishell, nb_cmd))
		return (minishell->command_line[nb_cmd].cmd);
	path = ft_split(ft_getenv(minishell->env, "PATH"), ':');
	i = -1;
	while (path[++i])
	{
		cmd = ft_strjoin(ft_strjoin(path[i], "/"), minishell->command_line[nb_cmd].cmd);
		if (access(cmd, X_OK) == 0)
			return (ft_free_split(path), cmd);
		free(cmd);
	}
	ft_free_split(path);
	return (NULL);
}

void	execute_command(char *cmd, t_minishell *minishell, int nb_cmd)
{
	if (execve(cmd,
		(char * const*)minishell->command_line[nb_cmd].args,
		minishell->env) == -1)
		exit(-1);
}
