/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_var_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:52:51 by lucmansa          #+#    #+#             */
/*   Updated: 2025/06/19 15:17:46 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rm_var_env(char **env, char *name)
{
	int	idx;
	int	len;

	idx = get_env_index(env, name);
	if (idx < 0)
		return ;
	free(env[idx]);
	len = tab_len(env);
	while (idx < len)
	{
		env[idx] = env[idx + 1];
		idx++;
	}
	env[idx] = NULL;
}
