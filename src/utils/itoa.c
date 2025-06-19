/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:29:36 by lucmansa          #+#    #+#             */
/*   Updated: 2025/06/19 15:16:08 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_countsize(long nb)
{
	size_t	s;

	s = 0;
	if (nb <= 0)
	{
		nb = -nb;
		s++;
	}
	while (nb)
	{
		nb = nb / 10;
		s++;
	}
	return (s);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	size;
	long	nb;

	nb = (long)n;
	if (nb == 0)
		return (ft_strdup("0"));
	size = ft_countsize(nb);
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	str[size] = '\0';
	while (nb)
	{
		str[--size] = nb % 10 + '0';
		nb = nb / 10;
	}
	return (str);
}
