/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:53:10 by norabino          #+#    #+#             */
/*   Updated: 2025/05/07 15:54:13 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	verif_quotes(char *str)
{
	int	simple_q;
	int	double_q;
	int	i;

	simple_q = 0;
	double_q = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == 34)
			double_q++;
		else if (str[i] == 39)
			simple_q++;
		i++;	
	}
	if (double_q % 2 != 0 || simple_q % 2 != 0)
		return (0);
	return (1);
}

char	*ft_substr(char *s, int start, int len)
{
	int		i;
	char	*str;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		len = 0;
	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = 0;
	return (str);
}

char	*ft_strjoin_char(char *s1, char c)
{
	char	*res;
	size_t	i;

	if (!c)
		return (exit(1), NULL);
	i = 0;
	if (s1)
		res = (char *)malloc((ft_strlen(s1) + 2) * sizeof(char));
	else
		res = (char *)malloc(2 * sizeof(char));
	if (!res)
		return (exit(1), NULL);
	if (s1)
	{
		while (s1[i])
		{
			res[i] = s1[i];
			i++;
		}
	}
	res[i] = c;
	res[i + 1] = '\0';
	if (s1)
		free(s1);
	return (res);
}

int	ft_count_seps(char *str)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			nb++;
		i++;
	}
	return (nb);
}