/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:55:50 by norabino          #+#    #+#             */
/*   Updated: 2025/05/07 15:56:05 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_nextpipe(char *line, int last_pipe)
{
	while (line[last_pipe] && line[last_pipe] != '|')
		last_pipe++;
	return (last_pipe);
}

static void	*ft_memmove(void *dest, void *src, size_t n)
{
	char		*d;
	char		*s;
	size_t		i;

	if (n != 0 && src == 0 && dest == 0)
		return (NULL);
	d = (char *)dest;
	s = (char *)src;
	i = -1;
	if (src >= dest)
	{
		while (++i < n)
			d[i] = s[i];
	}
	else
		while (n--)
			d[n] = s[n];
	return (dest);
}


char	*ft_strjoin(char *s1, char *s2)
{
	char	*res;
	size_t	len;
	int		i;

	i = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	res = malloc(sizeof(char) * len + 1);
	if (!res)
		return (0);
	ft_memmove(res, s1, ft_strlen(s1) + 1);
	while (res[i])
		i++;
	ft_memmove(&res[i], s2, ft_strlen(s2) + 1);
	return (res);
}


char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	c %= 256;
	while (s[i] != c)
	{
		if (s[i] == 0)
			return (0);
		i++;
	}
	return (&s[i]);
}