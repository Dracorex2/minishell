/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:09:34 by lucmansa          #+#    #+#             */
/*   Updated: 2025/05/07 17:28:39 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int echo(char **argv)
{
	int i = 1;
	int n = 0;

	if (argv[i] && argv[i][0] == '-' && argv[i][1] == 'n')
	{
		n = 1;
		i++;
	}
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (!n)
		printf("\n");
	return (0);
}
