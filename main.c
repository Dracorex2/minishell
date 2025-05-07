/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:39:19 by lucmansa          #+#    #+#             */
/*   Updated: 2025/05/07 15:59:29 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>


typedef struct s_minishell
{
	char	**env;
	char	*cmd;
	char	**args;
}	t_minishell;

char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);

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

int	tablelen(char **table)
{
	int	i;

	i = 0;
	while (table[i])
		i++;
	return (i);
}

void	execute_command(char *cmd, char * const* args, char **env)
{
	int ret;

	if (fork() == 0)
		if (execve(cmd, args, env) == -1)
			exit(-1);
	else
		wait(&ret);
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
	if (ft_strchr(minishell.cmd, '/') && access(minishell.cmd, X_OK))
		return (execute_command(minishell.cmd, minishell.args, minishell.env));
	path = ft_split(ft_getenv(minishell.env, "PATH"), ':');
	i = -1;
	while (path[++i])
	{
		cmd = ft_strjoin(ft_strjoin(path[i], "/"), minishell.cmd);
		if (access(cmd, X_OK))
			return (execute_command(minishell.cmd, minishell.args, minishell.env), free(cmd));
	}
	free(cmd);
	printf("%s: command not found\n", minishell.cmd);
}

int	main(int argc, char const **argv, char **env)
{
	t_minishell	minishell;

	(void)argc;
	(void)argv;
	minishell.env = env;
	minishell.cmd = "/bin/ls";
	minishell.args = ft_split(ft_strjoin(minishell.cmd, " -l -a"), ' ');
	search_command(minishell);
	while (1);
	return 0;
}
