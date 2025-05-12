/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:18:08 by lucmansa          #+#    #+#             */
/*   Updated: 2025/05/12 19:31:10 by lucmansa         ###   ########.fr       */
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

int execute_builtins(t_minishell *minishell, int nb_cmd)
{
	char	*cmd;
	char	**args;
	char	**env;

	cmd = minishell->command_line[nb_cmd].cmd;
	args = minishell->command_line[nb_cmd].splitted;
	env = minishell->env;
	if (ft_strcmp(cmd, "cd") == 0)
		return(ft_cd(args, env), 1);
	//else if (ft_strcmp(cmd, "pwd") == 0)
	//	return(ft_pwd(), 1);
	//else if (ft_strcmp(cmd, "export") == 0)
	//	return(ft_export(args, env), 1);
	//else if (ft_strcmp(cmd, "unset") == 0)
	//	return(ft_unset(args, env), 1);
	//else if (ft_strcmp(cmd, "env") == 0)
	//	return(ft_env(args, env), 1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return(ft_exit(minishell, nb_cmd), 1);
	else if (ft_strcmp(cmd, "echo") == 0)
		return(ft_echo(args), 1);
	else
		return (0);
}

void	execute_command(char *cmd, t_minishell *minishell, int nb_cmd)
{
	if (execve(cmd, (char * const*)minishell->command_line[nb_cmd].splitted, minishell->env) == -1)
		exit(-1);
}

char	*search_command(t_minishell *minishell, int nb_cmd) 
{
	char	**path;
	int		i;
	char	*cmd;

	if (ft_strchr(minishell->command_line[nb_cmd].cmd, '/') && access(minishell->command_line[nb_cmd].cmd, X_OK) == 0)
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

void	setup_pipes(t_minishell *minishell, int ***pipes)
{
	int	i;

	*pipes = NULL;
	if (minishell->nb_cmd <= 1)
		return ;
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

void	setup_child_pipes(t_minishell *minishell, int **pipes, int i)
{
	int	j;

	if (i > 0 && pipes)
		dup2(pipes[i - 1][0], STDIN_FILENO);
	if (i < minishell->nb_cmd - 1 && pipes)
		dup2(pipes[i][1], STDOUT_FILENO);
	if (!pipes)
		return ;
	j = 0;
	while (j < minishell->nb_cmd - 1)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
}

void	handle_parent_pipes(int **pipes, int i, int nb_cmd)
{
	if (i > 0 && pipes)
		close(pipes[i - 1][0]);
	if (i < nb_cmd - 1 && pipes)
		close(pipes[i][1]);
}

void	cleanup_pipes(int **pipes, int nb_pipes)
{
	int	i;

	if (!pipes)
		return ;
	i = 0;
	while (i < nb_pipes)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

void	execute_child(t_minishell *minishell, int **pipes, int i)
{
	char *cmdchr;

	cmdchr = search_command(minishell, i);
	if (!cmdchr)
	{
		printf("Command not found: %s\n", minishell->command_line[i].cmd);
		free(cmdchr);
		exit(0);
	}
	else
	{
		setup_child_pipes(minishell, pipes, i);
		if (minishell->command_line[i].redirect.aro || 
			minishell->command_line[i].redirect.ro)
			redirect_output(minishell, i);
		if (minishell->command_line[i].redirect.ri)
			redirect_input(minishell, i);
		execute_command(cmdchr, minishell, i);
	}
}

void	launch_exec(t_minishell *minishell)
{
	int	i;
	int	*pid;
	int	**pipes;

	setup_pipes(minishell, &pipes);
	pid = malloc(sizeof(int) * minishell->nb_cmd);
	i = 0;
	while (i < minishell->nb_cmd)
	{
		if (execute_builtins(minishell, i))
			return ;
		pid[i] = fork();
		if (pid[i] == 0)
			execute_child(minishell, pipes, i);
		else
			handle_parent_pipes(pipes, i, minishell->nb_cmd);
		i++;
	}
	wait_all_pid(pid, minishell->nb_cmd);
	cleanup_pipes(pipes, minishell->nb_cmd - 1);
}