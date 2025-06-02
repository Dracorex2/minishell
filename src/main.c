/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:01:06 by norabino          #+#    #+#             */
/*   Updated: 2025/06/02 17:25:18 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_minishell(t_minishell command)
{
	while (1)
	{
		command.line = readline("$> ");
		add_history(command.line);
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
			exec_cmd(&command);
			free_command_lines(&command);
		}
	}
	rl_clear_history();
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	minishell;

	printf("Welcome to MINISHELL\n");
	(void)argc;
	(void)argv;
	//env = NULL;
	minishell.env = cpy_env(env);
	upd_shlvl(&minishell);
	ft_minishell(minishell);
	return (0);
}