/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:32:33 by lucmansa          #+#    #+#             */
/*   Updated: 2025/05/05 16:34:09 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	main(int argc, char **argv, char **env)
{
	int	i;

	i = 0;
	(void)argc;
	(void)argv;
	while (env[++i])
		printf("%s\n", env[i]);
	return (0);
}