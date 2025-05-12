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

void redirect_input(t_minishell *minishell, int nb_cmd)
{
	int fd;

		if (minishell->command_line[nb_cmd].redirect.ri)
			fd = open(minishell->command_line[nb_cmd].redirect.ri, O_RDONLY);
		if (fd == -1)
			exit(-2);
		dup2(fd, STDIN_FILENO);
		close(fd);
}
void redirect_output(t_minishell *minishell, int nb_cmd)
{
	int fd;

	if (minishell->command_line[nb_cmd].redirect.aro)
		fd = open(minishell->command_line[nb_cmd].redirect.aro, O_WRONLY | O_CREAT | O_APPEND, 0644);	
	if (minishell->command_line[nb_cmd].redirect.ro)	
		fd = open(minishell->command_line[nb_cmd].redirect.ro, O_WRONLY | O_CREAT | O_TRUNC, 0644);	
	if (fd == -1)	
		exit(-2);	
	dup2(fd, STDOUT_FILENO);	
	close(fd);
}

void	execute_command(char *cmd, t_minishell *minishell, int nb_cmd)
{
	if (minishell->command_line->redirect.aro || minishell->command_line->redirect.ro)
		redirect_output(minishell, nb_cmd);
	if (minishell->command_line->redirect.ri)
		redirect_input(minishell, nb_cmd);
	if (execve(cmd, (char * const*)minishell->command_line[nb_cmd].splitted, minishell->env) == -1)
		exit(-1);
}

void	search_command(t_minishell *minishell, int nb_cmd) 
{
	char	**path;
	int		i;
	char	*cmd;

//	if (builtins(minishell.cmd))
//		return (execute_builtins(minishell.cmd, minishell.args, minishell.env));
	if (ft_strchr(minishell->command_line[nb_cmd].cmd, '/') && access(minishell->command_line[nb_cmd].cmd, X_OK) == 0)
		return (execute_command(minishell->command_line[nb_cmd].cmd, minishell, nb_cmd));
	path = ft_split(ft_getenv(minishell->env, "PATH"), ':');
	i = -1;
	while (path[++i])
	{
		cmd = ft_strjoin(ft_strjoin(path[i], "/"), minishell->command_line[nb_cmd].cmd);
		if (access(cmd, X_OK) == 0)
			return (execute_command(cmd, minishell, nb_cmd), free(cmd));
	}
	free(cmd);
	printf("%s: command not found\n", minishell->command_line[nb_cmd].cmd);
}


void wait_all_pid(int *pid, int nb_cmd)
{
	int i;
	int status;

	i = 0;
	while (i < nb_cmd)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	free(pid);
}

void launch_exec(t_minishell *minishell)
{
	int i;
	int *pid;

	i = 0;
	pid = malloc(sizeof(int) * minishell->nb_cmd);
	while (i < minishell->nb_cmd)
	{
		if (minishell->command_line[i].cmd)
		{
			pid[i] = fork();
			if (pid[i] == 0)
			{
				printf("%s\n", minishell->command_line[i].cmd);
				search_command(minishell, i);
			}
				
		}
		i++;
	}
	wait_all_pid(pid, minishell->nb_cmd);
}