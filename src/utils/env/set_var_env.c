/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_var_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:13:32 by lucmansa          #+#    #+#             */
/*   Updated: 2025/06/02 16:44:23 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char **set_var_env(char **env, char *name, char *value)
{
	int		idx;
	char	*new_var;
	int		size;

	if (!name || !env)
		return (env);
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
		env = ft_realloc(env, sizeof(char *) * size, sizeof(char *) * (size + 2));
		env[size] = new_var;
		env[size + 1] = NULL;
	}
	return (env);
}

		