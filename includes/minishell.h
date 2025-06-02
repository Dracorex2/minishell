/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:20:42 by norabino          #+#    #+#             */
/*   Updated: 2025/06/02 17:17:44 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>
#include <sys/stat.h>
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
	char	**hd_delimiters;
	char	*ro;
	char	*aro;
}	t_rdr;

typedef	struct s_command_line
{
	char **args;
	t_rdr	redirect;
}	t_command_line;

typedef struct s_minishell
{
	char	*line;
	int		nb_cmd;
	char	**env;
	int		rt_val;
	t_command_line	*command_line;
}	t_minishell;



/* FUNCTIONS */
int	ft_search(char *str, char c);
int ft_parse_commandline(t_minishell *command);
int ft_parse_commandsegment(t_minishell *command, int cmd_index, char *segment);
int	ft_print_tokens(t_minishell *command);
void free_command_lines(t_minishell *command);
void	ft_free_split(char **args);
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

void	ft_handle_redirections(t_minishell *command, char *segment, int cmd_index);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(char *s, int c);
int	ft_strcmp(char *s1, char *s2);
	
void launch_exec(t_minishell *minishell);

//heardoc
void ft_heredoc(char **ends, char ***stockage, int *i);
int	ft_parse_heredoc(t_minishell *command, int cmd_index, char *segment, int *begin_rdr, int *end_rdr);


//parsing
int	ft_cpt_heredoc(char *segment);
int	ft_strstrlen(char **str);
void	ft_set_spaces(char *segment, int begin, int length);


//builtins
int ft_echo(char **argv);
int	ft_exit(t_minishell *minishell, int idx);
int	ft_cd(char **argv, t_minishell *minishell);
int	ft_unset(t_minishell *minishell);
int	ft_export(t_minishell *minishell, char **args);
int	ft_env(char **env);
int	ft_pwd(void);

//len_utils
int		tab_len(char **tab);
int		ft_strlen(char *str);

int		is_builtin(t_minishell *minishell, int nb_cmd);

//////////////
void 	exec_cmd(t_minishell *minishell);

void	faild_schr(t_minishell *minishell, int i, char *schr);
int		execute_builtins(char *cmd, t_minishell *minishell, int nb_cmd);
//redirect
void	redirect_input(t_minishell *minishell, int idx);
void	redirect_output(t_minishell *minishell, int idx);
void	redirect_heredoc(t_minishell *minishell, int pipes[2], int ixd);

//single
void	redirect_single(t_minishell *minishell);
void	exec_single(t_minishell *minishell);

//multiple
void exec_multiple(t_minishell *minishell);

//env
char 	**cpy_env(char **env);
int		get_env_index(char **env, char *name);
void	rm_var_env(char **env, char *name);
char	**set_var_env(char **env, char *name, char *value);
char	*ft_getenv(char **env, char *var);
void	upd_shlvl(t_minishell *minishell);
char	*ft_get_value(char *env);
char	*ft_get_name(char *env);

//command
void	execute_command(char *cmd, t_minishell *minishell, int idx);
char	*search_command(t_minishell *minishell, int idx) ;

//memory
void	*ft_realloc(void *ptr, int old_size, int n_size);
void	ft_free_tabtab(char ***args);
//atoi
int		ft_atoi64(char *text, int64_t *res);
char	*ft_itoa(int n);

//str_cmp
int	ft_strncmp(char *s1, char *s2, int n);

void	ft_env_ARGS(t_minishell *minishell, char **args);
void	ft_env_HEREDOC(t_minishell *minishell, char **hd, int cmd_index);
int    ft_in_tab(char **tab, char *str);

void	exiting(t_minishell *minishell, int value);

char	*ft_strndup(char *str, int n);
#endif