/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:20:42 by norabino          #+#    #+#             */
/*   Updated: 2025/05/09 15:52:39 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>

# include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

# include <readline/readline.h>
# include <readline/history.h>

// ri <
// heredoc <<
// ro >
// aro >>

typedef struct s_redirections
{
	char	*ri;
	char	*heredoc;
	char	*ro;
	char	*aro;
}	t_rdr;

typedef	struct s_command_line
{
	char *cmd;
	char *args;
	char **splitted;
	t_rdr	redirect;
}	t_command_line;

typedef struct s_minishell
{
	char	*line;
	int		nb_cmd;
	char	**env;
	t_command_line	*command_line;
}	t_minishell;



/* FUNCTIONS */
int	ft_search(char *str, char c);
int ft_parse_commandline(t_minishell *command);
int ft_parse_commandsegment(t_minishell *command, int cmd_index, char *segment);
int	ft_print_tokens(t_minishell *command);
void free_command_lines(t_minishell *command);
void	ft_free_split(char **splitted);
int	ft_init(t_minishell *command, int nb_cmds);
int	ft_nextpipe(char *line, int last_pipe);
int	ft_nbpipes(char *line);
int	ft_ind_firstspace(char *str);
int	ft_parse_args_quotes(char *line);
char	*ft_handle_meta_chars(char *prompt, int begin);
char	*ft_strdup(char *str);
int	ft_count_seps(char *str);
char	*ft_strjoin_char(char *s1, char c);
char	*ft_substr(char *s, int start, int len);
int	verif_quotes(char *str);
int		ft_strlen(char *str);
char	**ft_split(char const *str, char c);

int	ft_handle_redirections(t_minishell *command, char *segment, int cmd_index);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(char *s, int c);

void launch_exec(t_minishell *minishell);
#endif