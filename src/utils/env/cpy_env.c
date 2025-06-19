/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:51:28 by lucmansa          #+#    #+#             */
/*   Updated: 2025/06/19 15:17:54 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cpy_env(char **env)
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
