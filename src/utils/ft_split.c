/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:34:43 by norabino          #+#    #+#             */
/*   Updated: 2025/06/19 15:31:02 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#include "stdio.h"
#include "stdlib.h"

char	*ft_strndup(char *str, int n)
{
	char	*tab;
	int		i;

	if (n < 0)
		return (ft_strdup(str));
	tab = (char *)malloc(n + 1);
	if (!tab)
		return (NULL);
	i = 0;
	while (str[i] && i < n)
	{
		tab[i] = str[i];
		i++;
	}
	tab[i] = 0;
	return (tab);
}

void	ft_check_quotes(char c, int *in_squotes, int *in_dquotes)
{
	if (c == '\'' && *in_dquotes == -1)
		*in_squotes = - (*in_squotes);
	if (c == '\"' && *in_squotes == -1)
		*in_dquotes = - (*in_dquotes);
}

int	ft_countwords(char *str, char c)
{
	int	i;
	int	j;
	int	in_charset;
	int	in_squotes;
	int	in_dquotes;

	i = 0;
	j = 0;
	in_charset = 0;
	in_squotes = -1;
	in_dquotes = -1;
	while (str[i])
	{
		ft_check_quotes(str[i], &in_squotes, &in_dquotes);
		if (str[i] != c && in_charset != 1)
		{
			in_charset = 1;
			j++;
		}
		if (str[i] == c && in_charset == 1)
		{
			if (in_dquotes == -1 && in_squotes == -1)
				j++;
		}
		i++;
	}
	return (j);
}

int	ft_zerosep(char *str, char ***dst)
{
	*dst = (char **)malloc(sizeof(char *) * 2);
	if (!dst)
		return (0);
	(*dst)[0] = ft_strndup((char *)str, ft_strlen((char *)str));
	if (!(*dst)[0])
		return (free(dst), 0);
	(*dst)[1] = 0;
	return (1);
}

char	**ft_split_line(char *str, char c)
{
	char	**res;
	int		i;
	int		start;
	int		end;
	int		in_squotes;
	int		in_dquotes;

	if (!ft_search(str, c))
		return (ft_zerosep(str, &res), res);
	res = (char **)malloc(sizeof(char *) * (ft_countwords(str, c) + 1));
	i = 0;
	start = 0;
	while (str[start] && i < ft_countwords(str, c))
	{
		while (str[start] && str[start] == c)
			start++;
		in_squotes = -1;
		in_dquotes = -1;
		end = start;
		while (str[end])
		{
			ft_check_quotes(str[end], &in_squotes, &in_dquotes);
			if (str[end] == c && in_squotes == -1 && in_dquotes == -1)
				break ;
			end++;
		}
		res[i] = ft_strndup(str + start, end - start);
		start = end;
		i++;
	}
	res[i] = 0;
	return (res);
}
