/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:27:00 by norabino          #+#    #+#             */
/*   Updated: 2025/05/05 14:48:32 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>
#include <stdio.h>

#include <readline/readline.h>
#include <readline/history.h>

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

void	ft_init_tokens(t_token *tokens, int size)
{
	int	i;

	i = 0;
	while (i <= size)
	{
		tokens[i].str = NULL;
		tokens[i].type = NONE;
		if (i < size)
			tokens[i].ind = i;
		else if (i >= size)
			tokens[i].ind = -1;
		i++;
	}
}

int	ft_init(t_minishell *command)
{
	int	token_count;

	token_count = ft_count_seps(command->line) + 2; // one because token_count = (ft_count_seps + 1), and one for \0
	command->tokens = (t_token *)malloc(sizeof(t_token) * token_count);
		if (!command->tokens)
			return (1);
	ft_init_tokens(command->tokens, token_count - 1);
	return (0);
}

int	ft_parse_args_quotes(char *line)
{
	int beg;

	// 34 = double quotes
	// 39 = single quote
	beg = 0;
	while (line[beg] && (line[beg] != '"' && line[beg] != 39))
		beg++;
	if (line[beg] != 34 && line[beg] != 39)
		return (printf("No quotes"), 1);
	printf("%s", ft_handle_meta_chars(line, beg + 1));
	return (0);
}


char	*ft_strdup(char *str)
{
	char	*tab;
	int		i;

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

int	ft_settokens(t_minishell *command)
{
	int	ind;
	int	space_index;

	ind = 0;
	space_index = ft_ind_firstspace(command->line);
	while (command->tokens[ind].ind != -1)
	{
		if (command->tokens[ind].ind == 0)
		{
			if (space_index == -1)
                command->tokens[ind].str = ft_strdup(command->line);
			else
				command->tokens[ind].str = ft_strdup(ft_substr(command->line, 0, space_index));
			command->tokens[ind].type = CMD;
		}
		else if (space_index != -1)
		{
			command->tokens[ind].str = ft_strdup(ft_substr(command->line, space_index + 1, ft_strlen(command->line) - (space_index + 1)));
			command->tokens[ind].type = ARG;
		}
		ind++;
	}
	return (0);
}

int	ft_print_tokens(t_minishell *command)
{
	int	ind;

	ind = 0;
	while (command->tokens[ind].ind != -1 && ind < 2)
	{
		if (command->tokens[ind].type != 2)
			printf("Token = '%s' | Type = ", command->tokens[ind].str);
		if (command->tokens[ind].type == 0)
			printf("'CMD'\n");
		if (command->tokens[ind].type == 1)
			printf("'ARG'\n");
		ind++;
	}
	//printf("\nind = %d\n", ind);
	return (0);
}

void free_tokens(t_minishell *command)
{
    int i = 0;
    
    if (!command->tokens)
        return;
        
    while (command->tokens[i].ind != -1)
    {
        if (command->tokens[i].str)
            free(command->tokens[i].str);
        i++;
    }
    free(command->tokens);
    command->tokens = NULL;
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
				printf("Error : Open quotes.\n");
				continue;
			}
			ft_init(&command);
			//ft_parse_args_quotes(command.line);
			ft_settokens(&command);
			ft_print_tokens(&command);
			//ft_exec(); // ta fonction pour ton programme
		}
		free_tokens(&command);
		free(command.line);
	}
	return (0);
}
