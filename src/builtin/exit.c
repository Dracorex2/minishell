/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:13:07 by lucmansa          #+#    #+#             */
/*   Updated: 2025/05/20 15:33:24 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(const char *nptr)
{
	int	nbr;
	int	i;
	int	sign;

	nbr = 0;
	i = 0;
	sign = 1;
	while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		if (nptr[i++] == '-')
			sign *= -1;
	while (nptr[i] >= '0' && nptr[i] <= '9')
		nbr = nbr * 10 + (nptr[i++] - '0');
	return (nbr * sign);
}
void	ft_exit_args(char **argv)
{
	int	i;

	i = 0;

	while (argv[1][i])
	{
		if (!ft_isdigit(argv[1][i]))
		{
			printf("exit: %s: numeric argument required\n", argv[1]);
			exit(255);
		}
		i++;
	}
	if (argv[2])
		printf("exit: too many arguments\n");
	else
		exit(ft_atoi(argv[1]));
}

void	ft_exit(t_minishell *minishell, int nb_cmd)
{
	if (minishell->command_line[nb_cmd].args)
	{
		ft_exit_args(minishell->command_line[nb_cmd].args);
	}
	else
		exit(0);
}
