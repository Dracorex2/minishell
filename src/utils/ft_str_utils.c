/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:53:10 by norabino          #+#    #+#             */
/*   Updated: 2025/05/14 17:28:01 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"



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
	char tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	return ft_strjoin(s1, tmp);
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