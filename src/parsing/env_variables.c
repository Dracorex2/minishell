/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:47:02 by lucmansa          #+#    #+#             */
/*   Updated: 2025/05/27 17:47:10 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_valid(char c)
{
	if ((c >= 'a' && c <= 'z') ||
		(c >= 'A' && c <= 'Z') ||
		(c >= '0' && c <= '9') ||
		(c == '_') || (c == '?'))
		return (1);
	return (0);
}

char	*ft_replace_var(t_minishell *minishell, char *str)
{
	char *res;

	if (str[0] == '$' && !ft_is_valid(str[1]))
		return (NULL);
	if (ft_getenv(minishell->env, str + 1))
		res = ft_strdup(ft_getenv(minishell->env, str + 1));
	else
		res = ft_strdup("");
	free(str);
	return (res);
}

void	ft_env_HEREDOC(t_minishell *minishell, char **hd, int cmd_index)
{
	int	i;

	i = 0;
	while (hd[i])
	{
		if (ft_search(hd[i], '$') && !ft_in_tab(minishell->command_line[cmd_index].redirect.hd_delimiters, hd[i]))
		{
			hd[i] = ft_replace_var(minishell, hd[i]);
			if (!hd[i])
				return ;
		}
		i++;
	}
}

void	ft_env_ARGS(t_minishell *minishell, char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (ft_search(args[i], '$'))
		{
			args[i] = ft_replace_var(minishell, args[i]);
			if (!args[i])
				return ;
		}
		i++;
	}
}
