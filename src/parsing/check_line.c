/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:54:01 by norabino          #+#    #+#             */
/*   Updated: 2025/06/23 19:09:44 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_error(char c)
{
	if (!c)
	{
		write(2, "minishell: syntax error near ", 29);
		write(2, "unexpected token 'newline'\n", 27);
	}
	else
	{
		write(2, "minishell: syntax error near unexpected token '", 47);
		write(2, &c, 1);
		write(2, "'\n", 2);
	}
}

int	check_redir(char *str, int i)
{
	i += is_redir(&str[i]);
	skip_spaces(str, &i);
	if (!str[i] || str[i] == '>' || str[i] == '<' || str[i] == '|')
		return (print_error(str[i]), 0);
	return (1);
}

int	check_pipes(char *str, int i)
{
	int	j;

	j = i - 1;
	while (j >= 0 && is_space(str[j]))
		j--;
	if (j == -1)
		return (print_error('|'), 0);
	i++;
	skip_spaces(str, &i);
	if (!str[i])
		return (print_error('|'), 0);
	return (1);
}

int	is_line_valid(char *str, int nb_cmd)
{
	int		i;
	char	quote;	

	i = 0;
	quote = 0;
	skip_spaces(str, &i);
	if (nb_cmd >= 2 && str[i] == '|')
		return (print_error(str[i]), 0);
	while (str[i])
	{
		if (is_quotes(&str[i]) && !quote)
			quote = str[i];
		else if (is_quotes(&str[i]) && quote)
			quote = 0;
		if (is_redir(&str[i]) && !quote && !check_redir(str, i))
			return (0);
		if (str[i] == '|' && !quote && !check_pipes(str, i))
			return (0);
		i++;
	}
	return (1);
}
