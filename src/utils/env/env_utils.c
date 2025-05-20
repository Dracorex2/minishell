/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:55:08 by lucmansa          #+#    #+#             */
/*   Updated: 2025/05/15 16:19:39 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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