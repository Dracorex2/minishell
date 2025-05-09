/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:18:08 by lucmansa          #+#    #+#             */
/*   Updated: 2025/05/09 16:01:33 by lucmansa         ###   ########.fr       */
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

void redirect_input(t_minishell *minishell)
{
	int fd;

		if (minishell->redirections->ri)
			fd = open(minishell->redirections->ri, O_RDONLY);
		if (fd == -1)
			exit(-2);
		dup2(fd, STDIN_FILENO);
		close(fd);
}
void redirect_output(t_minishell *minishell)
{
	int fd;

	if (minishell->redirections->aro)
		fd = open(minishell->redirections->aro, O_WRONLY | O_CREAT | O_APPEND, 0644);	
	if (minishell->redirections->ro)	
		fd = open(minishell->redirections->ro, O_WRONLY | O_CREAT | O_TRUNC, 0644);	
	if (fd == -1)	
		exit(-2);	
	dup2(fd, STDOUT_FILENO);	
	close(fd);
}

void	execute_command(char *cmd, t_minishell *minishell)
{
	int pid;
	int ret;

	pid = fork();
	if (pid == 0)
	{
		if (minishell->redirections->aro || minishell->redirections->ro)
			redirect_output(minishell);
		if (minishell->redirections->ri)
			redirect_input(minishell);
		if (execve(cmd, (char * const*)minishell->command_line->splitted, minishell->env) == -1)
			exit(-1);
	}
	else
	{
		waitpid(pid, &ret, 0);
		if (ret == -1)
			printf("Command execution failed\n");
		if (ret == -2)
			printf("Files not found\n");
	}
}

void	search_command(t_minishell *minishell)
{
	char	**path;
	int		i;
	char	*cmd;

//	if (builtins(minishell.cmd))
//		return (execute_builtins(minishell.cmd, minishell.args, minishell.env));
	if (ft_strchr(minishell->command_line->cmd, '/') && access(minishell->command_line->cmd, X_OK) == 0)
		return (execute_command(minishell->command_line->cmd, minishell));
	path = ft_split(ft_getenv(minishell->env, "PATH"), ':');
	i = -1;
	while (path[++i])
	{
		cmd = ft_strjoin(ft_strjoin(path[i], "/"), minishell->command_line->cmd);
		if (access(cmd, X_OK) == 0)
			return (execute_command(cmd, minishell), free(cmd));
	}
	free(cmd);
	printf("%s: command not found\n", minishell->command_line->cmd);
}

void launch_exec(t_minishell *minishell)
{
	int i;

	i = 0;
	while (i < minishell->nb_cmd)
	{
		if (minishell->command_line[i].cmd)
		{
			search_command(minishell);
			free(minishell->command_line[i].cmd);
			free(minishell->command_line[i].args);
			ft_free_split(minishell->command_line[i].splitted);
		}
		i++;
	}

}