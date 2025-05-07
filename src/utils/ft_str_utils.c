/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:53:10 by norabino          #+#    #+#             */
/*   Updated: 2025/05/07 16:26:31 by lucmansa         ###   ########.fr       */
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