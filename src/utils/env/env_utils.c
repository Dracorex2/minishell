/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:55:08 by lucmansa          #+#    #+#             */
/*   Updated: 2025/05/20 18:34:33 by lucmansa         ###   ########.fr       */
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