/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:47:34 by lucmansa          #+#    #+#             */
/*   Updated: 2025/06/23 14:41:41 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*convert_heredoc(t_minishell *mini, char *str)
{
	int	begin_q;
	int	end_q;

	begin_q = -1;
	end_q = -1;
	str = replace_all_var(mini, str);
	str = get_quotes_index(str, &begin_q, &end_q);
	return (str);
}

int	readline_heredoc(t_minishell *minishell, char *delimiter, int cmd_idx)
{
	char	*input;

	free(minishell->command_line[cmd_idx].redirect.ri);
	minishell->command_line[cmd_idx].redirect.ri = NULL;
	free(minishell->command_line[cmd_idx].redirect.heredoc);
	minishell->command_line[cmd_idx].redirect.heredoc = ft_strdup("");
	while (1)
	{
		input = readline("heredoc> ");
		if (!input)
			return (write(2, "minishell: warning: here-document end-of-file\n",
					46), 0);
		if (!ft_strcmp(input, delimiter))
			return (free(input), 0);
		minishell->command_line[cmd_idx].redirect.heredoc
			= convert_heredoc(minishell, ft_join_free(ft_join_free(
						minishell->command_line[cmd_idx].redirect.heredoc,
						input, 2), "\n", 0));
	}
	return (1);
}
