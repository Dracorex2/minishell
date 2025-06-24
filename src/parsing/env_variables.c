/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:47:02 by lucmansa          #+#    #+#             */
/*   Updated: 2025/06/24 17:32:47 by lucmansa         ###   ########.fr       */
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

static int	skip_var(char *str, int start)
{
	int	j;

	j = 0;
	while (ft_is_var(str[start + j]))
		j++;
	return (j);
}

static char	*get_var(t_minishell *minishell, char *str, int start, int *j)
{
	char	*tmp;
	char	*var;

	if (!str[start] || !ft_is_var(str[start]))
		var = ft_strdup("$");
	else if (str[start])
	{
		(*j) = skip_var(str, start);
		tmp = ft_substr(str, start, (*j));
		var = ft_strdup(ft_getenv(minishell->env, tmp));
		free(tmp);
	}
	return (var);
}

char	*ft_replace_var(t_minishell *minishell, char *str, int *start, int mod)
{
	int		j;
	int		tmp;
	char	*var;
	char	*res;

	(*start)++;
	var = NULL;
	tmp = 0;
	j = 0;
	if (str[(*start)] == '?' && ++tmp)
		var = ft_itoa(minishell->rt_val);
	else
		var = get_var(minishell, str, (*start), &j);
	res = ft_strndup(str, (*start) - 1);
	res = ft_join_free(ft_join_free(res, var, 0), &str[(*start) + j + tmp], 0);
	(*start) += ft_strlen(var) - 1;
	if (mod)
		free(str);
	return (free(var), res);
}

char	*replace_all_var(t_minishell *minishell, char *line)
{
	int		tab[3];

	ft_bzero((void *)tab, sizeof(int) * 3);
	while (line && line[tab[0]])
	{
		if (line[tab[0]] == '\'' && !tab[1])
			tab[1] = line[tab[0]];
		else if (line[tab[0]] == '\'' && tab[1])
			tab[1] = 0;
		if (line[tab[0]] == '<' && line[tab[0] + 1] == '<' && !tab[1])
		{
			tab[0] += 2;
			free(get_str(line, &tab[0]));
		}
		else if (!tab[1] && line[tab[0]] == '$')
		{
			line = ft_replace_var(minishell, line, &tab[0], tab[2]);
			tab[2] = 1;
		}
		else
			tab[0]++;
	}
	if (!tab[2])
		return (ft_strdup(line));
	return (line);
}
