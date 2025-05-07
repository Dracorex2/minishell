/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:57:06 by lucmansa          #+#    #+#             */
/*   Updated: 2025/05/07 16:29:13 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	count(const char *str, char charset)
{
	int	word;
	int	i;

	i = 0;
	word = 0;
	while (str[i])
	{
		while (str[i] == charset)
			i++;
		if (!str[i])
			return (word);
		word++;
		while (str[i] != charset && str[i] != 0)
			i++;
	}
	return (word);
}

static char	*ft_strdp(const char *src, char charset)
{
	int		len;
	char	*res;
	int		i;

	len = 0;
	while (src[len] && src[len] != charset)
		len++;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (0);
	i = -1;
	while (src[++i] != '\0' && src[i] != charset)
		res[i] = src[i];
	res[i] = '\0';
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		len;
	int		j;

	len = (count(s, c));
	tab = malloc((len + 1) * sizeof(char *));
	if (!tab)
		return (0);
	j = 0;
	i = 0;
	while (i < len)
	{
		while (s[j] == c)
			j++;
		tab[i] = ft_strdp(&s[j], c);
		while (s[j] != c && s[j] != 0)
			j++;
		while (s[j] == c)
			j++;
		i++;
	}
	tab[i] = 0;
	return (tab);
}
///////////////////////////////////////////////////////////////////////

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	*ft_memmove(void *dest, void *src, size_t n)
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

char	*ft_strchr(const char *s, int c)
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
	return ((char *)&s[i]);
}