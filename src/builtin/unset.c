/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:24:56 by lucmansa          #+#    #+#             */
/*   Updated: 2025/05/26 17:40:30 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_minishell *minishell)
{
	int	i;

	i = 0;
	while (minishell->command_line->args[++i])
	{
		printf("Unset: %s\n", minishell->command_line->args[i]);
		rm_var_env(minishell->env, minishell->command_line->args[i]);
	}
	return (0);
}
