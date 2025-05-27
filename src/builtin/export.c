/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 19:34:52 by lucmansa          #+#    #+#             */
/*   Updated: 2025/05/26 17:41:33 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sort_tab_p(char **env, int len)
{
	int		i;
	int		k;
	int		min;
	char	*tmp;

	i = -1;
	while (++i < len)
	{
		k = i + 1;
		min = i;
		while (k < len)
		{
			if (strcmp(env[min], env[k]) > 0)
				min = k;
			k++;
		}
		tmp = env[min];
		env[min] = env[i];
		env[i] = tmp;
		printf("%s\n", env[i]);
	}
}

int	ft_export(t_minishell *minishell, char **args)
{
	char	**env_cpy;

	env_cpy = cpy_env(minishell->env);
	if (!args)
	{
		env_cpy = cpy_env(minishell->env);
		sort_tab_p(env_cpy, tab_len(env_cpy));
		ft_free_split(env_cpy);
	}
	return (1);
}
