/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:01:06 by norabino          #+#    #+#             */
/*   Updated: 2025/05/14 17:10:47 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_minishell(t_minishell command)
{
	while (1)
	{
		command.line = readline("$> ");
		if (!command.line)
			break ;
		if (*command.line)
		{
			command.nb_cmd = ft_nbpipes(command.line) + 1;
			if (!verif_quotes(command.line))
			{
				printf("Error : Open quotes.\n");
				continue;
			}
			ft_parse_commandline(&command);
			//ft_print_tokens(&command);
			//ft_parse_args_quotes(command.line);
			exec_cmd(&command);
			free_command_lines(&command);
			free(command.line);
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	minishell;

	(void)argc;
	(void)argv;
	minishell.env = cpy_env(env);
	minishell.command_line = NULL;
	minishell.line = NULL;
	minishell.nb_cmd = 0;
	ft_minishell(minishell);
	return (0);
}