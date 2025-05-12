/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 19:09:32 by lucmansa          #+#    #+#             */
/*   Updated: 2025/05/12 19:18:59 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	update_pwd_env(char **env)
{
    char	cwd[200];
    char	*old_pwd;

    old_pwd = ft_getenv(env, "PWD");
    if (old_pwd)
        ft_setenv(env, "OLDPWD", old_pwd);
    if (getcwd(cwd, 200))
        ft_setenv(env, "PWD", cwd);
}

void	ft_cd(char **argv, char **env)
{
    char	*path;

    if (!argv[1])
    {
        path = ft_getenv(env, "HOME");
        if (!path)
        {
        	printf("cd: HOME not set\n");
            return ;
        }
    }
    else
        path = argv[1];
    chdir(path);
    update_pwd_env(env);
}