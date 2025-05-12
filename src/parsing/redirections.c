/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:25:48 by norabino          #+#    #+#             */
/*   Updated: 2025/05/09 17:10:59 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_search(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}
int	ft_get_index(char *segment, int *begin_rdr, int *end_rdr, int rdr_len)
{
	*begin_rdr += rdr_len;
	while (segment[*begin_rdr] && segment[*begin_rdr] == ' ')
			(*begin_rdr)++;
	if (!segment[*begin_rdr])
		return (0);
	*end_rdr = *begin_rdr;
	while (segment[*end_rdr] && segment[*end_rdr] != ' ')
		(*end_rdr)++;
	return (1);
}

void	ft_set_spaces(char *segment, int begin, int length)
{
    int	i;

    i = 0;
    while (i < length && segment[begin + i])
    {
        segment[begin + i] = ' ';
        i++;
    }
}

int	ft_handle_redirections(t_minishell *command, char *segment, int cmd_index)
{
	int	begin_rdr;
	int	end_rdr;
	int redirection;

	while (1)
	{
		if (!ft_search(segment, '<') && !ft_search(segment, '>'))
			return (1);
		redirection = 0;
		while (segment[redirection] != '<' && segment[redirection] != '>')
			redirection++;
		begin_rdr = redirection;
		end_rdr = 0;
		if ((segment[redirection] == '<' && segment[redirection + 1] == '<') || 
            (segment[redirection] == '>' && segment[redirection + 1] == '>'))
            begin_rdr++;
		// ri <
		if (segment[redirection] == '<' && segment[redirection + 1] != '<')
		{
			if (!ft_get_index(segment, &begin_rdr, &end_rdr, 1))
				return (0);
			command->command_line[cmd_index].redirect.ri = ft_substr(segment, begin_rdr, end_rdr - begin_rdr);
		}
		// heredoc <<
		else if (segment[redirection] == '<' && segment[redirection + 1] == '<')
		{
			if (!ft_get_index(segment, &begin_rdr, &end_rdr, 2))
				return (0);
			command->command_line[cmd_index].redirect.heredoc = ft_substr(segment, begin_rdr, end_rdr - begin_rdr);
		}
		// ro >
		else if (segment[redirection] == '>' && segment[redirection + 1] != '>')
		{
			if (!ft_get_index(segment, &begin_rdr, &end_rdr, 1))
				return (0);
			command->command_line[cmd_index].redirect.ro = ft_substr(segment, begin_rdr, end_rdr - begin_rdr);
		}
		// aro >>
		else if (segment[redirection] == '>' && segment[redirection + 1] == '>')
		{
			if (!ft_get_index(segment, &begin_rdr, &end_rdr, 2))
				return (0);
			command->command_line[cmd_index].redirect.aro = ft_substr(segment, begin_rdr, end_rdr - begin_rdr);
		}
		ft_set_spaces(segment, redirection, end_rdr - redirection);
	}
}
