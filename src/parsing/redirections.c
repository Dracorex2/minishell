/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 18:43:17 by lucmansa          #+#    #+#             */
/*   Updated: 2025/06/26 19:29:09 by lucmansa         ###   ########.fr       */
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

char	*replace_redir(char *seg)
{
	int	i;
	int	tmp;

	i = -1;
	while (seg[++i])
	{
		if (is_redir(&seg[i]))
		{
			ft_set_spaces(seg, i - 1, ft_which_redir(seg, &i));
			tmp = i;
			free(get_str(seg, &i));
			ft_set_spaces(seg, tmp, i - tmp + 1);
			break ;
		}
	}
	return (seg);
}

void	do_redir(t_minishell *minishell, char **segment, int *i, int cmd_idx)
{
	char	*redir;
	int		which_redir;
	int		begin_q;
	int		end_q;

	begin_q = 0;
	end_q = -1;
	which_redir = ft_which_redir(*segment, i);
	redir = get_str(*segment, i);
	redir = get_quotes_index(redir, &begin_q, &end_q);
	set_redir(minishell, redir, cmd_idx, which_redir);
	*segment = replace_redir(*segment);
	if (which_redir == 4)
		free(redir);
}

char	*handle_redir(t_minishell *minishell, int cmd_idx, char *segment)
{
	int		i;

	i = 0;
	while (segment[i])
	{
		if (is_redir(&segment[i]))
			do_redir(minishell, &segment, &i, cmd_idx);
		else
			i++;
	}
	return (segment);
}
