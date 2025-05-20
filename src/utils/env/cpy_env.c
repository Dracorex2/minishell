/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:51:28 by lucmansa          #+#    #+#             */
/*   Updated: 2025/05/15 14:51:41 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **cpy_env(char **env)
{
	char	**new;
	int		len;
	int		i;

	len = tab_len(env);
	new = malloc(sizeof(char *) * (len + 1));
	new[len] = NULL;
	i = -1;
	while (++i < len)
		new [i] = ft_strdup(env[i]);
	return (new);
}
