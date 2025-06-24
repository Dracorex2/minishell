/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:55:08 by lucmansa          #+#    #+#             */
/*   Updated: 2025/06/20 16:37:11 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*ft_get_name(char *env)
{
	char	*res;

	if (ft_strchr(env, '='))
		res = ft_strndup(env, (ft_strchr(env, '=') - env + 1));
	else
		res = ft_strdup(env);
	return (res);
}

char	*ft_get_value(char *env)
{
	char	*res;

	res = NULL;
	if (ft_strchr(env, '='))
		res = ft_strdup(ft_strchr(env, '=') + 1);
	return (res);
}

int	get_env_index(char **env, char *name)
{
	int		i;
	int		n_len;

	i = -1;
	n_len = ft_strlen(name);
	while (env[++i])
	{
		if (!ft_strncmp(env[i], name, n_len))
			return (i);
	}
	return (-1);
}

void	upd_shlvl(t_minishell *minishell)
{
	long int	shlvl;
	char		*tmp;

	shlvl = 0;
	ft_atoi64(ft_getenv(minishell->env, "SHLVL"), &shlvl);
	tmp = ft_itoa(shlvl + 1);
	minishell->env = set_var_env(minishell->env, "SHLVL", tmp);
	free(tmp);
}
