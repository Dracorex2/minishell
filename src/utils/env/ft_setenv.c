/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:13:32 by lucmansa          #+#    #+#             */
/*   Updated: 2025/05/14 19:27:33 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_env_index(char **env, char *name)
{
	int		i;
	int		n_len;
	char	*ptr;

	i = -1;
	n_len = ft_strlen(name);
	while (env[++i])
	{
		if (ft_strncmp(env[i], name, n_len))
			return (i);
	}
	return (-1);
}

static char *set_new_var(char *name, char *value)
{
	char	*var;
	char	*tmp;

	if (!value)
		var = ft_strdup(name);
	else
	{
		tmp = ft_strjoin(name, "=");
		var = ft_strjoin(tmp, value);
		free(tmp);
	}
	return (var);
}

void	ft_set_var_env(char **env, char *name, char *value)
{
	int		idx;
	char	*new_var;
	int		size;

	if (!name || !env)
		return ;
	new_var = set_new_var(name, value);
	idx = get_env_index(env, name);
	if (idx >= 0)
	{
		free(env[idx]);
		env[idx] = new_var;
	}
	else
	{
		size = tab_len(env);
		ft_realloc(env, size, size + 1);
		env[size] = new_var;
		env[size + 1] = NULL;
	}
}

		