/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:47:02 by lucmansa          #+#    #+#             */
/*   Updated: 2025/06/19 18:08:21 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_var(char c)
{
	if (!(('A' <= c && c <= 'Z')
			|| ('a' <= c && c <= 'z')
			|| ('0' <= c && c <= '9')
			|| c == '_'))
		return (0);
	return (1);
}

char	*ft_replace_var(t_minishell *minishell, char *str, int start)
{
	int		j;
	char	*var;
	char	*res;

	j = 1;
	start++;
	if (str[start] == '?')
		var = ft_itoa(minishell->rt_val);
	else
	{
		j = 0;
		while (ft_is_var(str[start + j]))
			j++;
		res = ft_substr(str, start, j);
		var = ft_getenv(minishell->env, res);
		free(res);
	}
	res = ft_strndup(str, start - 1);
	res = ft_join_free(res, var, 0);
	res = ft_join_free(res, &str[start + j], 0);
	return (res);
}

char	*replace_all_var(t_minishell *minishell, char *line)
{
	int		i;
	int		squotes;

	i = 0;
	squotes = 0;
	while (line && line[i])
	{
		if (line[i] == '\'' && !squotes)
			squotes = line[i];
		else if (line[i] == '\'' && squotes)
			squotes = 0;
		if (line[i] == '<' && line[i + 1] == '<' && !squotes)
		{
			i += 2;
			free(get_str(line, &i));
		}
		else if (!squotes && line[i] == '$')
			line = ft_replace_var(minishell, line, i);
		else
			i++;
	}
	return (line);
}
