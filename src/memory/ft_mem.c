/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:57:23 by norabino          #+#    #+#             */
/*   Updated: 2025/06/02 18:39:28 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_init(t_minishell *command, int nb_cmds)
{
	int	i;

	i = 0;
	command->command_line = malloc(nb_cmds * sizeof(t_command_line));
	if (!command->command_line)
		return (0);
	while (i < nb_cmds)
	{
		command->command_line[i].args = NULL;
		command->command_line[i].redirect.ri = NULL;
		command->command_line[i].redirect.heredoc = NULL,
		command->command_line[i].redirect.ro = NULL;
		command->command_line[i].redirect.aro = NULL;
		i++;
	}
	return (1);
}

void	ft_free_split(char **args)
{
	int	i;

	if (args == NULL)
		return ;
	i = 0;
	while (args[i])
	{
		free (args[i]);
		i++;
	}
	free(args);
}

void	ft_free_tabtab(char ***args)
{
	int	i;
	int j;

	if (args == NULL)
		return ;
	i = -1;
	while (args[++i])
	{
		j = -1;
		while (args[i][++j])
			free (args[i][j]);
		free (args[i]);
	}
	free(args);
}

void free_command_lines(t_minishell *command)
{
	int	i;

	if (!command)
		return ;
	i = 0;
	while (i < command->nb_cmd)
	{
		if (command->command_line[i].args)
			ft_free_split(command->command_line[i].args);
		if (command->command_line[i].redirect.ri)
			free(command->command_line[i].redirect.ri);
		if (command->command_line[i].redirect.heredoc)
			free(command->command_line[i].redirect.heredoc);
		if (command->command_line[i].redirect.ro)
			free(command->command_line[i].redirect.ro);
		if (command->command_line[i].redirect.aro)
			free(command->command_line[i].redirect.aro);
		i++;
	}
	if (command->command_line)
		free(command->command_line);
	if (command->line)
		free(command->line);
}