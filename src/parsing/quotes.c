/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:34:29 by lucmansa          #+#    #+#             */
/*   Updated: 2025/06/26 17:29:03 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*rm_quotes(char *str, int *begin_q, int *end_q)
{
	char	*res;
	char	*tmp;

	res = ft_strndup(str, *(begin_q));
	tmp = ft_substr(str, *(begin_q) + 1, (*(end_q) - *(begin_q)) - 1);
	res = ft_join_free(res, tmp, 1);
	tmp = ft_substr(str, *(end_q) + 1, ft_strlen(str) - *(end_q) + 1);
	res = ft_join_free(res, tmp, 1);
	*(begin_q) = -1;
	*(end_q) = -1;
	free(str);
	return (res);
}

char	*get_quotes_index(char *str, int *begin_q, int *end_q)
{
	int		i;
	char	quote;

	i = -1;
	quote = 0;
	while (str && str[++i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && !quote)
		{
			quote = str[i];
			*(begin_q) = i;
		}
		else if (str[i] == quote && quote)
		{
			quote = 0;
			*(end_q) = i;
		}
		if (*(begin_q) != -1 && *(end_q) != -1)
		{
			str = rm_quotes(str, begin_q, end_q);
			i -= 2;
		}
	}
	return (str);
}

char	**remove_quotes(char **args)
{
	int	i;
	int	begin_q;
	int	end_q;

	i = -1;
	begin_q = -1;
	end_q = -1;
	while (args[++i])
		args[i] = get_quotes_index(args[i], &begin_q, &end_q);
	return (args);
}
