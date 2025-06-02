/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 19:34:52 by lucmansa          #+#    #+#             */
/*   Updated: 2025/06/02 17:30:48 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sort_tab_p(char ***env, int len)
{
	int		i;
	int		k;
	int		min;
	char	**tmp;

	i = -1;
	while (++i < len)
	{
		k = i + 1;
		min = i;
		while (k < len)
		{
			if (ft_strcmp(env[min][0], env[k][0]) > 0)
				min = k;
			k++;
		}
		tmp = env[min];
		env[min] = env[i];
		env[i] = tmp;
		if (env[i][1])
			printf("declare -x %s=\"%s\"\n", env[i][0], env[i][1]);
		else
			printf("declare -x %s\n", env[i][0]);
	}
}

static char	***split_cpy_env(char **env)
{
	char	***new;
	int		len;
	int		i;

	len = tab_len(env);
	new = malloc(sizeof(char **) * (len + 1));
	new[len] = NULL;
	i = -1;
	while (++i < len)
	{
		new[i] = malloc(sizeof(char *) * 3);
		new[i][0] = ft_strndup(env[i], ft_strchr(env[i], '=') - env[i]);
		new[i][1] = NULL;
		if (ft_strchr(env[i], '='))
			new[i][1] = ft_strdup(ft_strchr(env[i], '=') + 1);
		new[i][2] = NULL;
	}
	return (new);
}

static int	ton_pere_le_chien(char *str)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (i == 0 && ('0' <= str[i] && str[i] <= '9'))
			return (0);
		if (str[i] == '+' && i == (ft_strlen(str) - 1))
			return (1);
		if (!(('A' <= str[i] && str[i] <= 'Z')
				|| ('a' <= str[i] && str[i] <= 'z')
				|| ('0' <= str[i] && str[i] <= '9') || str[i] == '_'))
			return (0);
	}
	return (1);
}

static int	ta_mere_la_pute(t_minishell *minishell, char *name, char *value)
{
	if (!ton_pere_le_chien(name))
		return (1);
	if (name[ft_strlen(name) - 1] == '+')
	{
		name[ft_strlen(name) - 1] = '\0';
		minishell->env = set_var_env(minishell->env, name,
				ft_strjoin(ft_getenv(minishell->env, name), value));
	}
	else
		minishell->env = set_var_env(minishell->env, name, value);
	free(name);
	return (0);
}

int	ft_export(t_minishell *minishell, char **args)
{
	char	***env_cpy;
	int		i;

	if (!args[1])
	{
		env_cpy = split_cpy_env(minishell->env);
		sort_tab_p(env_cpy, tab_len((char **)env_cpy));
		ft_free_tabtab(env_cpy);
		return (1);
	}
	i = 0;
	while (args[++i])
	{
		if (ft_strchr(args[i], '=') == NULL)
		{
			if (get_env_index(minishell->env, args[i]) == -1)
				ta_mere_la_pute(minishell, ft_strdup(args[i]), NULL);
		}
		else
			ta_mere_la_pute(minishell, ft_get_name(args[i]),
				ft_get_value(args[i]));
	}
	return (1);
}
