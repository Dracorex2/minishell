/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:20:42 by norabino          #+#    #+#             */
/*   Updated: 2025/05/05 14:49:07 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*typedef enum e_token_type
{
	INPUT,
	HEREDOC,
	TRUNC,
	APPEND,
	PIPE,
	CMD,
	ARG,
}	t_token_type;*/

typedef enum e_token_type
{
	CMD,
	ARG,
	NONE,
}	t_token_type;

typedef	struct s_token
{
	char			*str;
	t_token_type	type;
	int				ind;
}	t_token;

typedef struct s_minishell
{
	char	*line;
	t_token	*tokens;
}	t_minishell;


size_t	ft_strlen(const char *str);