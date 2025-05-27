/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:48:00 by lucmansa          #+#    #+#             */
/*   Updated: 2025/05/27 17:48:03 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_print_tokens(t_minishell *minishell)
{
	int	i = 0;
	int	j;

	while (i < minishell->nb_cmd)
	{
		printf("Command %d:\n", i + 1);
		if (minishell->command_line[i].args)
		{
			printf(" Arguments :\n");
			j = 0;
			while (minishell->command_line[i].args[j])
			{
				printf("  [%d] %s\n", j, minishell->command_line[i].args[j]);
				j++;
			}
		}
        if (minishell->command_line[i].redirect.ri || minishell->command_line[i].redirect.heredoc || minishell->command_line[i].redirect.ro || minishell->command_line[i].redirect.aro)
            printf("\n Redirections :\n");
        if (minishell->command_line[i].redirect.ri)
            printf("  RI = %s\n", minishell->command_line[i].redirect.ri);
        if (minishell->command_line[i].redirect.heredoc)
            printf("  HEREDOC =\n%s\n", minishell->command_line[i].redirect.heredoc);
        if (minishell->command_line[i].redirect.ro)
            printf("  RO = %s\n", minishell->command_line[i].redirect.ro);
        if (minishell->command_line[i].redirect.aro)
            printf("  ARO = %s\n", minishell->command_line[i].redirect.aro);
		printf("\n\n");
		i++;
	}

	return (0);
}

int ft_parse_commandsegment(t_minishell *minishell, int cmd_index, char *segment)
{
    int space_index;
    int start = 0;
    
    ft_handle_redirections(minishell, segment, cmd_index);
    while (segment[start] && segment[start] == ' ')
        start++;
    space_index = start;
    while (segment[space_index] && segment[space_index] != ' ')
        space_index++;
    minishell->command_line[cmd_index].args = ft_split(segment, ' ');
    ft_env_ARGS(minishell, minishell->command_line[cmd_index].args);
    return (0);
}

int ft_parse_commandline(t_minishell *minishell)
{
    int i = 0;
    int pipe_start = 0;
    int pipe_end = 0;
    char *cmd_segment;

    minishell->nb_cmd = ft_nbpipes(minishell->line) + 1;
    ft_init(minishell, minishell->nb_cmd);
    while (i < minishell->nb_cmd)
    {
        pipe_end = ft_nextpipe(minishell->line, pipe_start);
        cmd_segment = ft_substr(minishell->line, pipe_start, (pipe_end - pipe_start));
        ft_parse_commandsegment(minishell, i, cmd_segment);
        pipe_start = pipe_end + 1;
        i++;
        free(cmd_segment);
    }
    return (0);
}
