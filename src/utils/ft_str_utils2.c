/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:54:39 by norabino          #+#    #+#             */
/*   Updated: 2025/06/23 18:19:15 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strdup(char *str)
{
	char	*tab;
	int		i;

	if (!str)
		return (NULL);
	tab = (char *)malloc(ft_strlen(str) + 1);
	if (!tab)
		return (NULL);
	i = 0;
	while (str[i])
	{
		tab[i] = str[i];
		i++;
	}
	tab[i] = 0;
	return (tab);
}

int	ft_ind_firstspace(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	if (!str[i])
		return (-1);
	return (i);
}

int	ft_nbpipes(char *line)
{
	int		i;
	int		cpt;
	char	quote;

	i = 0;
	cpt = 0;
	quote = 0;
	while (line[i])
	{
		if (is_quotes(&line[i]) && !quote)
			quote = line[i];
		else if (is_quotes(&line[i]) && quote)
			quote = 0;
		if (line[i] == '|' && !quote)
			cpt++;
		i++;
	}
	return (cpt);
}

void	ft_free_dst(char ***dst, int *i)
{
	while ((*i)--)
		free(*dst[*i]);
	free(*dst);
}

int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\f'
		|| c == '\n' || c == '\r' || c == '\v')
		return (1);
	return (0);
}
