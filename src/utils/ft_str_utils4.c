/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:01:43 by norabino          #+#    #+#             */
/*   Updated: 2025/06/24 15:37:43 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1)
		return (1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && i < n && s1[i])
		i++;
	if (i == n)
		return (0);
	return (s1[i] - s2[i]);
}

void	ft_set_spaces(char *segment, int begin, int length)
{
	int	i;

	i = 0;
	while (i < length && segment[begin + i])
	{
		segment[begin + i] = ' ';
		i++;
	}
}

int	ft_strstrlen(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void	ft_print_string(char *str)
{
	int	i;

	i = 0;
	printf("\n\n");
	if (!str)
	{
		printf("NULL\n");
		return ;
	}
	while (str[i])
	{
		printf("str[%d] = %c\n", i, str[i]);
		i++;
	}
	printf("\n");
}
