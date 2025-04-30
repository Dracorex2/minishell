/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:27:00 by norabino          #+#    #+#             */
/*   Updated: 2025/04/28 19:06:28 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

#include <stdlib.h>
#include <stdio.h>

#include <readline/readline.h>
#include <readline/history.h>

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
	while (i < len && s[i])
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = 0;
	return (str);
}

char	*ft_handle_meta_chars(char *prompt, int begin)
{
	int		i;
	int		size;
	char	*string;

	i = begin;
	while (prompt[i] != 34 && prompt[i] != 39)
		i++;
	size = i - begin;
	string = ft_substr(prompt, begin, size);
	if (!string)
		return (NULL);
	return (string);
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

void	ft_init_tokens(t_token *tokens, char *line, int size)
{
	int	i;

	i = 0;
	(void)line;
	while (i <= size)
	{
		tokens[i].str = NULL;
		//tokens[i].type = NULL;
		if (i < size)
			tokens[i].ind = i;
		else
			tokens[i].ind = -1;
		i++;
	}
}

int	ft_init(t_minishell command)
{
	int	token_count;

	token_count = ft_count_seps(command.line);
	command.tokens = (t_token *)malloc(sizeof(t_token) * token_count + 2);
		if (!command.tokens)
			return (1);
	ft_init_tokens(command.tokens, command.line, token_count);
	return (0);
}

int	ft_parse_args(char *line)
{
	int beg;

	// 34 = double quotes
	// 39 = single quote
	beg = 0;
	while (line[beg] && (line[beg] != 34 && line[beg] != 39))
		beg++;
	if (line[beg] != 34 && line[beg] != 39)
		return (printf("No quotes"), 1);
	printf("%s", ft_handle_meta_chars(line, beg + 1));
	return (0);
}

int	main()
{
	t_minishell	command;

	while (1)
	{
		command.line = readline("$> ");
		if (!command.line)
			break ;
		if (*command.line)
		{
			if (!verif_quotes(command.line))
			{
				printf("Open quotes");
				continue;
			}
			ft_init(command);
			//ft_parse_args(command.line);
			//ft_exec(); // ta fonction pour ton programme
		}
		free(command.line);
	}
	return (0);
}