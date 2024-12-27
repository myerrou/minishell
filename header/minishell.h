/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myerrou <myerrou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 09:32:56 by bjniane           #+#    #+#             */
/*   Updated: 2024/11/28 10:57:39 by myerrou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libf/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define BUFF_SIZE 4096

typedef struct s_env
{
	int				flag;
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef enum e_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HERDOC,
	APPEND,
	OR,
	SC,
}					t_type;

typedef struct s_token
{
	char			*content;
	t_type			type;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_sig
{
	int				exit_status;
	int				flag;
	int				execute;
	char			*rand;
	t_list			*trash;
}					t_sig;

typedef struct s_file
{
	char			*file;
	int				redir_in;
	int				redir_out;
	int				herdoc;
	int				append;
	int				expand;
	int				ambiguous;
	struct s_file	*next;
}					t_file;

typedef struct s_node
{
	char			**cmd;
	t_type			type;
	t_file			*file;
	t_type			op;
	struct s_node	*next;
}					t_node;

typedef struct s_var
{
	char			**result;
	char			*str;
	char			*env_value;
	char			*new_res;
	int				i;
	int				y;
	int				start;
	int				singqt;
	int				doublqt;
	t_env			*envp;
}					t_var;

// Lexer
void				init_shell(char **env, t_env **envp);
void				shel_loop(t_env *envp);
int					main(int ac, char **av, char **env);
int					is_whitespace(int c);
int					is_special(int c);
int					special_char(int c);
int					handle_error(t_token *current);
int					word_error(t_token *current);
int					syntax_error(t_token *token);
void				handle_redirection(t_token **token, char *str, int *i);
void				handle_special(t_token **token, char *str, int *i);
int					ft_inside_qt(char c, int *singl, int *doubl);
void				handle_word(t_token **token, char *str, int *i);
void				handle_pipe(t_token **token, char *str, int *i);
void				pipe_redirection(t_token **token, char *str, int *i);
int					ft_lstsize(t_token *lst);
void				ft_lstadd_back(t_token **token, t_token *new_token);
t_token				*ft_lstlast(t_token *lst);
t_token				*ft_lstnew(char *content, t_type type);
t_token				*ft_lexer(char *str);

// Parsing
t_file				*ft_last(t_file *lst);
void				ft_lstadd_node(t_node **node, t_node *new_node);
int					handle_files(t_token *current, t_node *node);
char				*quote_in_file(t_file *file, char *line, char *new_file,
						int *i);
char				*func_file(char *line, char *new_file, int *i);
int					process_file(t_file *file, char *line);
size_t				size_2d_len(char **str);
int					compare_character(char c1, char c2);
char				*whitespace_changed(char *str);
void				split_export_var(t_token *current, t_node *node,
						char **expanded);
void				first_cmd(t_node *node, char **expanded);
void				other_cmd(t_node *node, char **expanded);
int					cmds_conditions(t_token *current, t_env *envp,
						t_node *node);
t_node				*parsing(t_token **token, t_env *envp);

// expand
char				*append_char(char *str, char c);
int					helper_function(char *line, t_var *var);
int					handle_qt_after(char *line, t_var *var);
int					var_expansion(char *line, t_var *var);
int					not_expanded(char *line, t_var *var);
void				function_quote(char *line, t_var *var);
int					help_herdoc(char *line, t_var *var);
int					expanssion_herdoc(char *line, t_var *var);
int					without_expanssion(char *line, t_var *var);
int					handle_expanssion(char *line, t_var *var);
int					handle_non_dollar(char *line, t_var *var);
int					second_expand(char *line, t_var *var);
char				**expand(char *line, t_env *envp);
char				**expand_herdoc(char *line, t_env *envp);

// Builtins
void				reset_file(void);
int					ft_echo(char **args);
int					ft_env(t_env *env);
void				ft_exit(char **cmd);
int					ft_pwd(void);
int					ft_unset(char **args, t_env **env);
int					ft_export(char **args, t_env *env);
int					ft_cd(char **args, t_env *env);

// still need something for export and unset
char				*get_token_name(char *dest, const char *src);
//

// Envirement
int					valid_envirement(const char *env);
int					content_len(const char *env);
char				*envirement_content(char *env);
char				*get_token_content(char *arg, t_env *env);
size_t				size_env(t_env *env);
char				**env_to_tab(t_env *env);
t_env				*env_init(t_env *env, char **env_array);
void				increment_shell_level(t_env *env);
void				sort_envirement(t_env *env);
void				sort_and_print_env(t_env *env);
//

//  Execute
int					error_message(t_env *env, char *path);
int					is_it_builtin(char *command);
int					execute_the_builtin(t_node *parsed, t_env *env);
char				**paths_split(char *path);
int					execution(t_node *parsed, t_env *env);
void				execute_command(t_env *env, t_node *node);
int					execute_pipe(t_env *env, t_node *token);
int					redirecting(t_node *node, t_env *envp);
char				*ft__herdoc(t_token *token, t_file *file, t_env *env,
						int i);
void				ft_signal(int sig);
int					test_quote(char *str);
int					count_herdoc(t_token *node);
// Extra exec
void				update_env_value(t_env *env, char *arg);
int					ft_execvpe(char *file, char **argv, t_env *env);
void				exec_cmd_help(t_env *env, t_node *node);
char				*ft_getenv(t_env *env, char *name);
int					is_in_env(t_env *env, char *args);
int					env_add(char *value, t_env *env);
int					error_mess(int error, const char *arg);
void				ft_sigint_handler(int sig);
void				ft_handler(int sig);
void				err_messo(char *args);
//

extern t_sig		g_sig;

#endif