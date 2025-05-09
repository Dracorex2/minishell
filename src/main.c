/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main->c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student->42->fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:01:06 by norabino          #+#    #+#             */
/*   Updated: 2025/05/07 16:36:57 by lucmansa         ###   ########->fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_minishell(t_minishell *command)
{
	
	while (1)
	{
		command->line = readline("$> ");
		if (!command->line)
			break ;
		if (*command->line)
		{
			command->nb_cmd = ft_nbpipes(command->line) + 1;
			if (!verif_quotes(command->line))
			{
				printf("Error : Open quotes->\n");
				continue;
			}
			ft_parse_commandline(command);
			ft_print_tokens(command);
			//ft_parse_args_quotes(command->line);
			search_command(*command);
		}
		free_command_lines(command);
		free(command->line);
	}
}

int	main(int argc, char const **argv, char **env)
{
	t_minishell	command;

	(void)argc;
	(void)argv;
	command.env = env;

	command.redirections = malloc(sizeof(t_rdr));
	command.redirections->ro = "f";
	ft_minishell(&command);
	return (0);
}