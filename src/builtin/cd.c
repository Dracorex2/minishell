/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 19:09:32 by lucmansa          #+#    #+#             */
/*   Updated: 2025/05/20 17:04:14 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	update_pwd_env(char **env)
{
	char	cwd[200];
	char	*old_pwd;

	old_pwd = ft_getenv(env, "PWD");
	if (old_pwd)
		set_var_env(env, "OLDPWD", old_pwd);
	if (getcwd(cwd, 200))
		set_var_env(env, "PWD", cwd);
}

int	ft_cd(char **argv, char **env)
{
	char	*path;

	if (!argv)
	{
		path = ft_getenv(env, "HOME");
		if (!path)
		{
			printf("cd: HOME not set\n");
			return (0);
		}
	}
	else
		path = argv[1];
	chdir(path);
	update_pwd_env(env);
	return (0);
}