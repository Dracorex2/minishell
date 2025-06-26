/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:47:34 by lucmansa          #+#    #+#             */
/*   Updated: 2025/06/26 16:53:22 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*convert_heredoc(t_minishell *mini, char *str)
{
	int		begin_q;
	int		end_q;
	char	*res;

	begin_q = -1;
	end_q = -1;
	res = replace_all_var(mini, str);
	res = get_quotes_index(res, &begin_q, &end_q);
	free(str);
	return (res);
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
						input, 1), "\n", 0));
	}
	return (1);
}
