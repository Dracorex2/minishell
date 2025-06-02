/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:13:07 by lucmansa          #+#    #+#             */
/*   Updated: 2025/06/02 17:17:21 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdint.h>

void	exiting(t_minishell *minishell, int value)
{
	ft_free_split(minishell->env);
	free_command_lines(minishell);
	exit(value);
}

static int	ft_exitnoarg(t_minishell *minishell)
{
	write(STDERR_FILENO, "exit\n", 5);
	exiting(minishell, 0);
	return (1);
}

int	ft_exit(t_minishell *minishell, int idx)
{
	int64_t	exit_code;

	if (!minishell->command_line[idx].args[1])
		return (ft_exitnoarg(minishell));
	else if (tab_len(minishell->command_line[idx].args) == 2)
	{
		if (ft_atoi64(minishell->command_line[idx].args[1], &exit_code))
		{
			write(STDERR_FILENO, "exit: ", 6);
			write(STDERR_FILENO, minishell->command_line[idx].args[1],
				ft_strlen(minishell->command_line[idx].args[1]));
			write(STDERR_FILENO, ": numeric argument required\n", 28);
			exit_code = 2;
		}
		else
			write(STDERR_FILENO, "exit\n", 5);
		exiting(minishell, exit_code % 256);
	}
	write(STDERR_FILENO, "exit\nexit: too many arguments\n", 30);
	return (1);
}
