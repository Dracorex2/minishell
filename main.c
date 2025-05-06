/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:39:19 by lucmansa          #+#    #+#             */
/*   Updated: 2025/05/06 15:23:48 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_minishell
{
	char	**env;
	char	*cmd;
	char	**args;
}	t_minishell;

char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);

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

void	execute_command(t_minishell minishell, char **env)
{
	char	**path;
	int		i;
	char	*cmd;

	cmd = ft_strjoin("./builtin/", minishell.cmd);
	if (access(cmd, X_OK) == 0 && execve(cmd, minishell.args, env) == -1)
		return (free(cmd));
	free(cmd);
	path = ft_split(ft_getenv(env, "PATH"), ':');
	i = -1;
	while (path[++i])
	{
		cmd = ft_strjoin(ft_strjoin(path[i], "/"), minishell.cmd);
		if (access(cmd, X_OK) == 0 && execve(cmd, minishell.args, env) == -1)
			return (free(cmd));
		free(cmd);
	}
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
	execute_command(minishell, minishell.env);
	return 0;
}
