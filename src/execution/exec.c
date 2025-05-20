/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:18:08 by lucmansa          #+#    #+#             */
/*   Updated: 2025/05/20 15:32:48 by lucmansa         ###   ########.fr       */
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

int	is_builtin(t_minishell *minishell, int nb_cmd)
{
	char	*cmd;

	cmd = minishell->command_line[nb_cmd].cmd;
	if (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "unset") == 0 || 
		ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "exit") == 0 ||
		ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "env") == 0 ||
		ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int execute_builtins(char *cmd, t_minishell *minishell, int nb_cmd)
{
	char	**args;

	args = minishell->command_line[nb_cmd].args;
	if (ft_strcmp(cmd, "cd") == 0)
		return(ft_cd(args, minishell->env));
	else if (ft_strcmp(cmd, "pwd") == 0)
		return(ft_pwd());
	else if (ft_strcmp(cmd, "export") == 0)
		return(ft_export(minishell, args));
	else if (ft_strcmp(cmd, "unset") == 0)
		return(ft_unset(minishell), 0);
	else if (ft_strcmp(cmd, "env") == 0)
		return(ft_env(minishell->env), 1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (ft_exit(minishell, nb_cmd), -1);
	else if (ft_strcmp(cmd, "echo") == 0)
		return(ft_echo(args));
	else
		return (-1);
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
	while (j < minishell->nb_cmd)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
}

void	close_parent_pipes(int **pipes, int i)
{
	close(pipes[i][0]);
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
	setup_child_pipes(minishell, pipes, i);
	if (minishell->command_line[i].redirect.aro || 
		minishell->command_line[i].redirect.ro)
		redirect_output(minishell, i);
	if (minishell->command_line[i].redirect.ri)
		redirect_input(minishell, i);
	if (!execute_builtins(cmdchr, minishell, i))
		execute_command(cmdchr, minishell, i);
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
		printf("Command%i\n", minishell->nb_cmd);
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

///////////////////////////////////////////////////////////////////////////////////////////////



void exec_cmd(t_minishell *minishell)
{
	if (minishell->nb_cmd == 1)
		exec_single(minishell);
	//else
	//	exec_multiple()

}