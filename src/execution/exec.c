/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:18:08 by lucmansa          #+#    #+#             */
/*   Updated: 2025/05/07 17:30:14 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_getenv(char **env, char *var)
{
	int	i;
	int	j;

	i = -1;
	while (env[++i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
		{
			if (env[i][j] != var[j])
				break ;
			j++;
		}
		if (env[i][j] == '=' && var[j] == '\0')
			return (&env[i][j + 1]);
	}
	return (NULL);
}

void	execute_command(char *cmd, char **args, char **env)
{
	int ret;
	int pid;

	pid = fork();
	if (pid == 0)
	{
		if (execve(cmd, (char * const*)args, env) == -1)
			exit(-1);
	}
	else
		waitpid(pid, &ret, 0);
	if (ret == -1)
		printf("Command execution failed\n");
}

void	search_command(t_minishell minishell)
{
	char	**path;
	int		i;
	char	*cmd;

//	if (builtins(minishell.cmd))
//		return (execute_builtins(minishell.cmd, minishell.args, minishell.env));
	if (ft_strchr(minishell.command_line->cmd, '/') && access(minishell.command_line->cmd, X_OK) == 0)
		return (execute_command(minishell.command_line->cmd, minishell.command_line->splitted, minishell.env));
	path = ft_split(ft_getenv(minishell.env, "PATH"), ':');
	i = -1;
	while (path[++i])
	{
		cmd = ft_strjoin(ft_strjoin(path[i], "/"), minishell.command_line->cmd);
		if (access(cmd, X_OK) == 0)
			return (execute_command(cmd, minishell.command_line->splitted, minishell.env), free(cmd));
	}
	free(cmd);
	printf("%s: command not found\n", minishell.command_line->cmd);
}