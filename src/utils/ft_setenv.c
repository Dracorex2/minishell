/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:13:32 by lucmansa          #+#    #+#             */
/*   Updated: 2025/05/12 19:21:14 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_env_index(char **env, char *name)
{
    int		i;
    int		name_len;
    char	*ptr;

    i = 0;
    name_len = ft_strlen(name);
    while (env[i])
    {
        ptr = ft_strchr(env[i], '=');
        if (ptr && (ptr - env[i]) == name_len && 
            !ft_strcmp(env[i], name))
            return (i);
        i++;
    }
    return (-1);
}

static int	ft_env_len(char **env)
{
    int	i;

    i = 0;
    while (env[i])
        i++;
    return (i);
}

void	ft_setenv(char **env, char *name, char *value)
{
    int		idx;
    char	*new_var;

    if (!name || !value || !env)
        return ;
    new_var = ft_strjoin(ft_strjoin(name, "="), value);
    if (!new_var)
        return ;
    idx = get_env_index(env, name);
    if (idx >= 0)
    {
        free(env[idx]);
        env[idx] = new_var;
    }
    else
    {
        idx = ft_env_len(env);
        env[idx] = new_var;
        env[idx + 1] = NULL;
    }
}