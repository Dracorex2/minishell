/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:50:42 by lucmansa          #+#    #+#             */
/*   Updated: 2025/06/19 15:10:44 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*ft_realloc(void *ptr, int old_size, int n_size)
{
	void	*new_ptr;
	int		min_size;
	int		i;

	if (!ptr)
		return (malloc(n_size));
	if (old_size == n_size)
		return (ptr);
	new_ptr = malloc(n_size);
	if (!new_ptr)
		return (NULL);
	min_size = old_size;
	if (n_size < old_size)
		min_size = n_size;
	i = -1;
	while (++i < min_size)
		((char *)new_ptr)[i] = ((char *)ptr)[i];
	return (free(ptr), new_ptr);
}
