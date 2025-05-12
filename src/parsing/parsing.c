/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:27:00 by norabino          #+#    #+#             */
/*   Updated: 2025/05/09 17:17:17 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_print_tokens(t_minishell *command)
{
	int	i = 0;
	int	j;

	while (i < command->nb_cmd)
	{
		printf("Command %d:\n", i + 1);
		//printf("CMD = %s\n", command->command_line[i].cmd);
		//printf("ARGS = %s\n\n", command->command_line[i].args);
		if (command->command_line[i].splitted)
		{
			printf(" Arguments :\n");
			j = 0;
			while (command->command_line[i].splitted[j])
			{
				printf("  [%d] %s\n", j, command->command_line[i].splitted[j]);
				j++;
			}
		}
        if (command->command_line[i].redirect.ri || command->command_line[i].redirect.heredoc || command->command_line[i].redirect.ro || command->command_line[i].redirect.aro)
            printf("\n Redirections :\n");
        if (command->command_line[i].redirect.ri)
            printf("  RI = %s\n", command->command_line[i].redirect.ri);
        if (command->command_line[i].redirect.heredoc)
            printf("  HEREDOC = %s\n", command->command_line[i].redirect.heredoc);
        if (command->command_line[i].redirect.ro)
            printf("  RO = %s\n", command->command_line[i].redirect.ro);
        if (command->command_line[i].redirect.aro)
            printf("  ARO = %s\n", command->command_line[i].redirect.aro);
		printf("\n\n");
		i++;
	}

	return (0);
}

void ft_remove_redirection_tokens(char **tokens)
{
    int i = 0;
    int j = 0;

    while (tokens[i])
    {
        if (ft_search(tokens[i], '<') || ft_search(tokens[i], '>'))
            free(tokens[i]);
        else
            tokens[j++] = tokens[i];
        i++;
    }
    tokens[j] = NULL;
}

int ft_parse_commandsegment(t_minishell *command, int cmd_index, char *segment)
{
    int space_index;
    int start = 0;
    
    ft_handle_redirections(command, segment, cmd_index);
    while (segment[start] && segment[start] == ' ')
        start++;
    space_index = start;
    while (segment[space_index] && segment[space_index] != ' ')
        space_index++;
        
    if (segment[space_index] == '\0')
    {
        command->command_line[cmd_index].cmd = ft_strdup(segment + start);
        command->command_line[cmd_index].args = ft_strdup(segment);
    }
    else
    {
        command->command_line[cmd_index].cmd = ft_strdup(
            ft_substr(segment, start, space_index - start));
        command->command_line[cmd_index].args = ft_strdup(segment);
        command->command_line[cmd_index].splitted = ft_split(segment, ' ');
        //ft_remove_redirection_tokens(command->command_line[cmd_index].splitted);
    }
    return (0);
}

int ft_parse_commandline(t_minishell *command)
{
    int i = 0;
    int pipe_start = 0;
    int pipe_end = 0;
    char *cmd_segment;

    command->nb_cmd = ft_nbpipes(command->line) + 1;
    ft_init(command, command->nb_cmd);
    while (i < command->nb_cmd)
    {
        pipe_end = ft_nextpipe(command->line, pipe_start);
        cmd_segment = ft_substr(command->line, pipe_start, (pipe_end - pipe_start));
        ft_parse_commandsegment(command, i, cmd_segment);
        pipe_start = pipe_end + 1;
        i++;
        free(cmd_segment);
    }
    
    return (0);
}
