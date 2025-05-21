/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:18:08 by lucmansa          #+#    #+#             */
/*   Updated: 2025/05/21 15:47:55 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"



int	is_builtin(t_minishell *minishell, int nb_cmd)
{
	char	*cmd;

	cmd = minishell->command_line[nb_cmd].cmd;
	if (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "unset") == 0 || 
		ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "exit") == 0 ||
		ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "env") == 0 ||
		ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int execute_builtins(char *cmd, t_minishell *minishell, int nb_cmd)
{
	char	**args;

	args = minishell->command_line[nb_cmd].args;
	if (ft_strcmp(cmd, "cd") == 0)
		return(ft_cd(args, minishell->env));
	else if (ft_strcmp(cmd, "pwd") == 0)
		return(ft_pwd());
	else if (ft_strcmp(cmd, "export") == 0)
		return(ft_export(minishell, args));
	else if (ft_strcmp(cmd, "unset") == 0)
		return(ft_unset(minishell), 0);
	else if (ft_strcmp(cmd, "env") == 0)
		return(ft_env(minishell->env), 1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (ft_exit(minishell, nb_cmd), -1);
	else if (ft_strcmp(cmd, "echo") == 0)
		return(ft_echo(args));
	else
		return (-1);
}



///////////////////////////////////////////////////////////////////////////////////////////////



void exec_cmd(t_minishell *minishell)
{
	if (minishell->nb_cmd == 1)
		exec_single(minishell);
	else
		exec_multiple(minishell);
	printf("return value : %i\n", minishell->rt_val);
}