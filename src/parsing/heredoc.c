/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:43:43 by norabino          #+#    #+#             */
/*   Updated: 2025/05/20 15:38:06 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char **ft_realloc_tab(char **old, int new_size)
{
	char **new;
	int i;

	new = malloc((new_size + 1)* sizeof(char *));
	i = 0;
	if (!new)
	{
		if (old)
			ft_free_split(old);
		return (NULL);
	}
	while (old && old[i] && i < new_size - 1)
	{
		new[i] = ft_strdup(old[i]);
		if (!new[i])
        {
            while (i--)
                free(new[i]);
            free(new);
            return (NULL);
        }
		free(old[i]);
		i++;
	}
	new[i] = NULL;
	free(old);
	return (new);
}

void ft_heredoc(char **ends, char ***stockage, int *i)
{
    char *input;
    int current_end;
	int	end_count;
   
	current_end = 0;
	end_count = ft_strstrlen(ends);
    while (ends[current_end])
    {
        *i = 0;
        if (*stockage)
		{
            ft_free_split(*stockage);
			*stockage = NULL;
		}
        *stockage = malloc(sizeof(char *) * 1);
        if (!*stockage)
            return;
        (*stockage)[0] = NULL;
        while (1)
        {
            input = readline("heredoc> ");
            if (!input)
                return;
            if (!ft_strcmp(input, ends[current_end]))
            {
                free(input);
                break;
            }
			if (current_end == end_count - 1)
			{
	            *stockage = ft_realloc_tab(*stockage, *i + 1);
	            if (!*stockage)
	            {
	                free(input);
	                return;
	            }
	            (*stockage)[*i] = ft_strdup(input);
	            if (!((*stockage)[*i]))
	            {
	                free(input);
	                (*stockage)[*i] = NULL;
	                return;
	            }
	            (*i)++;
			}
            free(input);
        }
        current_end++;
    }
    if (*stockage)
        (*stockage)[*i] = NULL;
}

char	*ft_format_stockage(char **stockage)
{
	char	*new;
	char	*temp;
	int	i;
	int	total_size;

	i = 0;
	total_size = 0;
	while (stockage[i])
	{
		total_size += ft_strlen(stockage[i]) + 1;
		i++;
	}
	new = ft_strdup("");
	if (!new)
		return (NULL);
	i = 0;
	while (stockage[i])
	{
		temp = ft_strjoin(new, stockage[i]);
		free(new);
		if (!temp)
			return (NULL);
		new = temp;
		temp = ft_strjoin(new, "\n");
		free(new);
		if (!temp)
			return (NULL);
		new  = temp;
		i++;
	}
	return (new);
}

int	ft_parse_heredoc(t_minishell *command, int cmd_index, char *segment, int *begin_rdr, int *end_rdr)
{
	char **stockage;
	int	i;
	int	begin_hd;
	char **ends;	
	int	cpt_delimiter;
	int	j;
	int	pos;
	char	*substr;

	begin_hd = 0;
	while (segment[begin_hd])
	{
   		if (segment[begin_hd] == '<')
    	{
        	*end_rdr = begin_hd;
        	while (segment[*end_rdr] && (segment[*end_rdr] == ' ' || segment[*end_rdr] == '<'))
            	(*end_rdr)++;
        	ft_set_spaces(segment, begin_hd, *end_rdr - begin_hd);
        	begin_hd = *end_rdr;
    	}
    	else
        	begin_hd++;
	}
	pos = *begin_rdr;
	substr = ft_substr(segment, *begin_rdr, ft_strlen(segment) - *begin_rdr);
	ends = ft_split(substr, ' ');
	free(substr);
	if (!ends)
		return (0);
	stockage = malloc(sizeof(char *) * 1);
	if (!stockage)
		return (ft_free_split(ends), 0);
	stockage[0] = NULL;
	i = 0;
	ft_heredoc(ends, &stockage, &i);
	cpt_delimiter = ft_strstrlen(ends);
	if (cpt_delimiter > 0)
	{
		j = 0;
		while (j < cpt_delimiter)
		{
			while (segment[pos] && segment[pos] == ' ')
				pos++;
			pos += ft_strlen(ends[j]);
			j++;
			while (j < cpt_delimiter && segment[pos] && segment[pos] == ' ')
				pos++;
		}
		*end_rdr = pos;
	}
	else
		*end_rdr = *begin_rdr;
	ft_free_split(ends);
	command->command_line[cmd_index].redirect.heredoc = ft_format_stockage(stockage);
	return (i);
}