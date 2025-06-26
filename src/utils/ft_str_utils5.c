/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_utils5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 18:24:56 by lucmansa          #+#    #+#             */
/*   Updated: 2025/06/26 19:22:29 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	have_spaces(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (is_space(str[i]))
			return (free(str), 1);
	return (free(str), 0);
}
