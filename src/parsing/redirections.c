/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 18:43:17 by lucmansa          #+#    #+#             */
/*   Updated: 2025/06/23 14:41:17 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_which_redir(char *redir, int *i)
{
	if (redir[*i] == '<' && redir[*i + 1] != '<')
		return ((*i)++, 1);
	if (redir[*i] == '>' && redir[*i + 1] != '>')
		return ((*i)++, 2);
	if (redir[*i] == '>' && redir[*i + 1] == '>')
		return ((*i) += 2, 3);
	if (redir[*i] == '<' && redir[*i + 1] == '<')
		return ((*i) += 2, 4);
	return (-1);
}

static void	set_redir(t_minishell *minishell, char *redir,
	int cmd_index, int which_redir)
{
	if (which_redir == 1)
	{
		free(minishell->command_line[cmd_index].redirect.ri);
		minishell->command_line[cmd_index].redirect.ri = redir;
		free(minishell->command_line[cmd_index].redirect.heredoc);
		minishell->command_line[cmd_index].redirect.heredoc = NULL;
	}
	if (which_redir == 2)
	{
		free(minishell->command_line[cmd_index].redirect.ro);
		minishell->command_line[cmd_index].redirect.ro = redir;
		free(minishell->command_line[cmd_index].redirect.aro);
		minishell->command_line[cmd_index].redirect.aro = NULL;
	}
	if (which_redir == 3)
	{
		free(minishell->command_line[cmd_index].redirect.aro);
		minishell->command_line[cmd_index].redirect.aro = redir;
		free(minishell->command_line[cmd_index].redirect.ro);
		minishell->command_line[cmd_index].redirect.ro = NULL;
	}
	if (which_redir == 4)
		readline_heredoc(minishell, redir, cmd_index);
}

void	do_redir(t_minishell *minishell, char **segment, int *i, int cmd_idx)
{
	char	*redir;
	int		which_redir;
	int		start[2];

	start[0] = *i;
	which_redir = ft_which_redir(*segment, i);
	skip_spaces(*segment, i);
	start[1] = *i;
	redir = get_str(*segment, i);
	set_redir(minishell, redir, cmd_idx, which_redir);
	ft_set_spaces(*segment, start[0], is_redir(&(*segment)[start[0]]));
	ft_set_spaces(*segment, start[1], ft_strlen(redir));
	if (which_redir == 4)
		free(redir);
}

char	*handle_redir(t_minishell *minishell, int cmd_idx, char *segment)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (segment[i])
	{
		if (is_quotes(&segment[i]) && !quote)
			quote = segment[i];
		else if (is_quotes(&segment[i]) && quote)
			quote = 0;
		if (is_redir(&segment[i]) && !quote)
			do_redir(minishell, &segment, &i, cmd_idx);
		else
			i++;
	}
	return (segment);
}
