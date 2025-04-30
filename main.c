/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:39:19 by lucmansa          #+#    #+#             */
/*   Updated: 2025/04/28 17:54:38 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);

int	tablelen(char **table)
{
	int	i;

	i = 0;
	while (table[i])
		i++;
	return (i);
}

int main(int argc, char const *argv[], char *env[])
{
	char **path;
	path = ft_split(getenv("PATH"), ':');
	int i = -1;

	while (path[++i])
		path [i] = ft_strjoin(path[i], "/");
	i = -1;
	while (path[++i])
		execve(ft_strjoin(path[i], argv[1]), (char * const*)&argv[1], env);
	if (i >= tablelen(path))
		printf("%s: command not found\n", argv[1]);
	return 0;
}
