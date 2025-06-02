/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:32:33 by lucmansa          #+#    #+#             */
/*   Updated: 2025/06/02 16:36:52 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"

int	ft_env(char **env)
{
	int	i;

	i = -1;
	if (!env)
		return (-1);
	while (env[++i] != NULL)
	{
		if (!ft_strchr(env[i], '='))
			;
		else
			printf("%s\n", env[i]);
	}
	return (0);
}
