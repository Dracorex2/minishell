/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:20:42 by norabino          #+#    #+#             */
/*   Updated: 2025/05/14 19:17:42 by lucmansa         ###   ########.fr       */
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

char	**ft_split(char const *str, char c);

int	ft_handle_redirections(t_minishell *command, char *segment, int cmd_index);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(char *s, int c);
int	ft_strcmp(char *s1, char *s2);
	
void launch_exec(t_minishell *minishell);

char	*ft_getenv(char **env, char *var);

int ft_echo(char **argv);
void	ft_exit(t_minishell *minishell, int nb_cmd);
void	ft_cd(char **argv, char **env);

void	ft_setenv(char **env, char *name, char *value);

//len_utils
int		tab_len(char **tab);
int		ft_strlen(char *str);

int		is_builtin(t_minishell *minishell, int nb_cmd);

//////////////
void 	exec_cmd(t_minishell *minishell);

void	faild_schr(t_minishell *minishell, int i, char *schr);
int		execute_builtins(char *cmd, t_minishell *minishell, int nb_cmd);
//redirect
void	redirect_input(t_minishell *minishell, int nb_cmd);
void	redirect_output(t_minishell *minishell, int nb_cmd);

//single
void	redirect_single(t_minishell *minishell);
void	exec_single(t_minishell *minishell);

//env
char **cpy_env(char **env);

//command
void	execute_command(char *cmd, t_minishell *minishell, int nb_cmd);
char	*search_command(t_minishell *minishell, int nb_cmd) ;

//memory
void	*ft_realloc(void *ptr, int old_size, int n_size);

//str_cmp
int	ft_strncmp(char *s1, char *s2, int n);

#endif