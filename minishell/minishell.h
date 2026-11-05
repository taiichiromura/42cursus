/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:27:40 by ktakeru           #+#    #+#             */
/*   Updated: 2025/09/18 16:35:15 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _POSIX_C_SOURCE 200809L

# include <ctype.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <unistd.h>

# define IN_NONE 0
# define IN_SQ 1
# define IN_DQ 2
# define ERR_START 1
# define ERR_REDIR 2
# define ERR_PIPE 3
# define ERR_TWOOPS 4
# define ERR_OPEN_PAREN 5
# define ERR_CLOSE_PAREN 6
# define IN_NONE 0
# define IN_SQ 1
# define IN_DQ 2
# define MAX_FD_SCAN 1024

/* ---------------- Token type ---------------- */
typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_AND,
	T_OR,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_APPEND,
	T_REDIR_HEREDOC,
	T_OPEN_PAREN,
	T_CLOSE_PAREN,
	T_SEMI,
	T_EOF,
	T_NEW_LINE
}								t_token_type;

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
	NODE_SEQUENCE,
	NODE_SUBSHELL
}								t_node_type;

typedef enum e_redirect_type
{
	RED_IN,
	RED_OUT,
	RED_APPEND,
	RED_HEREDOC
}								t_redirect_type;

typedef enum e_builtin_type
{
	BUILTIN_NONE,
	BUILTIN_CD,
	BUILTIN_ECHO,
	BUILTIN_EXPORT,
	BUILTIN_UNSET,
	BUILTIN_ENV,
	BUILTIN_EXIT,
	BUILTIN_PWD
}								t_builtin_type;

typedef struct s_env_var
{
	char						*key;
	char						*value;
	int							is_exported;
	struct s_env_var			*next;
}								t_env_var;

typedef struct s_redirect
{
	t_redirect_type				type;
	char						*filename;
	struct s_redirect			*next;
	int							is_last_heredoc;
}								t_redirect;

typedef struct s_command
{
	char						**args;
	t_redirect					*redirects;
	t_builtin_type				builtin;
	struct s_command			*next;
}								t_command;

typedef struct s_token
{
	t_token_type				type;
	char						*value;
	struct s_token				*next;
}								t_token;

typedef struct s_ast_node
{
	t_node_type					type;
	t_command					*cmd;
	struct s_ast_node			*left;
	struct s_ast_node			*right;
}								t_ast_node;

typedef struct s_buildctx
{
	char						***out_ref;
	int							*n_ref;
	int							*cap_ref;
	t_env_var					*env;
}								t_buildctx;

typedef struct s_dollarctx
{
	const char					*raw;
	size_t						*i;
	int							q;
	char						**out;
	t_env_var					*env;
}								t_dollarctx;

typedef struct s_shell_context
{
	int							last_exit_status;
}								t_shell_context;

typedef struct s_exec_context
{
	t_command					*cmd;
	t_env_var					**env_list;
	t_shell_context				*shell_context;
	int							*saved_stdin;
	int							*saved_stdout;
}								t_exec_context;

typedef struct s_heredoc_context
{
	char						*tmp_filename;
	int							status;
	int							do_redirect;
	t_shell_context				*shell_context;
}								t_heredoc_context;

typedef struct s_heredoc_data
{
	const char					*delimiter;
	int							fd_tmp;
	char						**envp;
	int							expand;
	t_shell_context				*context;
}								t_heredoc_data;

typedef struct s_pipeline_context
{
	t_command					*cmd_list;
	t_env_var					**env_list;
	t_shell_context				*context;
	int							pipe_in[2];
	int							pipe_out[2];
}								t_pipeline_context;

int								contains_wildcard(const char *s);
char							**expand_wildcard_token(const char *pattern);
int								match_pattern(const char *pattern,
									const char *str);
int								ft_isspace(int c);

/* ---------------- Global val ---------------- */
extern volatile sig_atomic_t	g_sigint_received;

/* ----------------01_main---------------- */
t_env_var						*setup_env_and_signal(char **envp);
int								execute_command_line(char *line,
									t_env_var **env_list,
									t_shell_context *context);
int								minishell_loop(t_env_var **env_list,
									t_shell_context *context);
int								main(int argc, char **argv, char **envp);
int								is_blank_line(char *line);

/* ----------------02_create environment list---------------- */
t_env_var						*create_env_node(char *envp_str);
t_env_var						*create_env_list(char **envp);

/* ----------------03_setup signals---------------- */
void							setup_parent_wait_signals(void);
void							setup_child_signals(void);
void							setup_parent_signals(void);

/* ----------------04_lexer---------------- */
t_token							*lexer(const char *line);
t_token							*new_token(t_token_type type, const char *start,
									size_t len);
void							add_token(t_token **head, t_token *new_tok);
t_token							*handle_single1(const char *line, size_t *i);
t_token							*handle_single2(const char *line, size_t *i);
char							*expand_exit_status(const char *str);

/* ----------------05_validate syntax---------------- */
void							test_parse_error(const char *input);
int								validate_syntax(t_token *tokens);
int								is_redir(int t);
int								is_op(int t);
int								is_cmd_start_token(int type);

/* ----------------06_parser---------------- */
t_builtin_type					identify_builtin(char *cmd_name);

int								parse_tokens_into_cmd(t_command *cmd,
									t_token **cur, int *argc, int *cap);
int								handle_redirection_token(t_command *cmd,
									t_token **cur);
int								handle_word_token(t_command *cmd, t_token **cur,
									int *argc, int *cap);
/* ----------------08_ast---------------- */
int								execute_pipe_node(t_ast_node *node,
									t_env_var **env_list,
									t_shell_context *context);
int								execute_logical_and(t_ast_node *node,
									t_env_var **env_list,
									t_shell_context *context);
int								execute_logical_or(t_ast_node *node,
									t_env_var **env_list,
									t_shell_context *context);
int								execute_sequence_node(t_ast_node *node,
									t_env_var **env_list,
									t_shell_context *context);
int								execute_ast(t_ast_node *node,
									t_env_var **env_list,
									t_shell_context *context);
t_command						*create_new_command(t_ast_node *node);
t_command						*ast_to_command_list(t_ast_node *node);
t_redirect						*copy_redirects(t_redirect *original);

/*08 expand*/
typedef struct s_expand_ctx
{
	const char					*raw;
	size_t						*i;
	int							q;
	char						**out;
	t_env_var					*env;
}								t_expand_ctx;

/* ----------------09_execute_cmd---------------- */
int								execute_command(t_command *cmd,
									t_env_var **env_list,
									t_shell_context *context);
int								is_variable_assignment(t_command *cmd);
int								handle_variable_assignment(char *arg,
									t_env_var **env_list);
int								execute_with_redirect(t_command *cmd,
									t_env_var **env_list,
									t_shell_context *context);
void							update_underscore_var(t_command *cmd,
									t_env_var **env_list);

/* ----------------10_builtin_cmd---------------- */
int								builtin_echo(char **args);
int								builtin_pwd(void);
int								builtin_env(t_command *cmd, t_env_var *env_list,
									t_shell_context *context);
int								execute_builtin(t_command *cmd,
									t_env_var **env_list,
									t_shell_context *context);
char							*my_getenv_val(t_env_var *env_list,
									const char *key);
int								builtin_cd(char **args, t_env_var **env_list,
									t_shell_context *context);
int								print_sorted_env(t_env_var *env_list);
int								builtin_export(char **args,
									t_env_var **env_list,
									t_shell_context *context);
int								handle_export_arg(char *arg,
									t_env_var **env_list);
int								is_valid_varname(const char *key);
int								builtin_unset(char **args,
									t_env_var **env_list);
int								ft_atoll(const char *str, long long *res,
									char **endptr);
long long						check_exit_args(char **args,
									long long *exit_code_ptr,
									t_shell_context *context);
int								builtin_exit(char **args,
									t_shell_context *context);
int								set_env_var(t_env_var **env_list,
									const char *key, const char *value,
									int is_exported);

/* ----------------11_external_cmd---------------- */
void							execute_child_process(char **argv,
									t_env_var *env_list,
									t_redirect *redirect_list,
									t_shell_context *context);
int								execute_external_command(t_command *cmd,
									t_env_var *env_list,
									t_shell_context *context);
int								find_command_path(char *cmd,
									t_env_var *env_list, char **cmd_path);
char							**generate_envp_for_execve(t_env_var *env_list);

/* ----------------12_pipeline---------------- */
void							execute_pipe_child(t_pipeline_context *p_ctx);
void							execute_pipe_parents(t_pipeline_context *p_ctx);
pid_t							execute_pipe_loop(t_pipeline_context *p_ctx);
int								execute_pipeline(t_command *cmd_list,
									t_env_var **env_list,
									t_shell_context *context);
int								wait_all_child_get_last_status(pid_t last_pid,
									t_shell_context *context);
void							handle_command_execution(t_command *current_cmd,
									t_env_var **env_list,
									t_shell_context *context);
void							handle_pipe_redirection(int *pipe_in,
									int *pipe_out);
void							handle_redirections_execution(t_command *cmd,
									t_env_var **env_list,
									t_shell_context *context);

/* ----------------13_subshell---------------- */
int								execute_subshell(t_ast_node *subshell_node,
									t_env_var **env_list,
									t_shell_context *context);

/* ----------------14_redirect---------------- */
int								handle_red_in(t_redirect *current_list);
int								handle_red_out(t_redirect *current_list);
int								handle_red_append(t_redirect *current_list);
int								handle_redirection(t_redirect *redirect_list,
									char **envp, t_shell_context *context);
int								handle_red_heredoc(t_redirect *current_list,
									char **envp, t_shell_context *context);
int								prepare_heredoc_file(char **tmp_filename_ptr,
									int *fd_tmp_ptr);
char							*append_value(char *res, char *value);
void							execute_child_heredoc(const char *delimiter,
									int fd_tmp, char **envp,
									t_shell_context *context);
char							*remove_quotes(const char *str);
int								is_quoted(const char *delimiter);
char							*expand_env_heredoc(char *line, char **envp,
									t_shell_context *context);
int								hd_dup2_error(int fd_tmp, char *tmp_filename);
int								wait_for_child_heredoc(pid_t pid, int *status);

/* ----------------98_free---------------- */
void							free_tokens(t_token *tokens);
void							free_redirects(t_redirect *redir);
void							free_command(t_command *cmd);
void							free_ast(t_ast_node *node);
void							free_array(char **envp_array);
void							free_env_list(t_env_var *env_list);
void							cleanup_exec(char *line, t_token *tokens,
									t_ast_node *ast);
void							free_command_list(t_command *cmd);

/* ----------------99_error---------------- */
void							pipe_error(void);
void							fork_error(void);
int								open_error(void);
int								fd_error(char *filename);
int								dup2_error(void);
int								fd_tmp_open_error(char *tmp_filename);
int								fd_tmp_fork_error(int fd_tmp,
									char *tmp_filename);
void							exit_with_error(int status, char *line,
									t_token *tokens, t_ast_node *ast);

/* ----------------libft---------------- */
int								ft_printf(const char *format, ...);
int								ft_fprintf(int fd, const char *format, ...);
char							*ft_strdup(const char *src);
char							*ft_strchr(const char *s, int c);
size_t							ft_strlen(const char *str);
char							*ft_strchr(const char *s, int c);
void							ft_putstr_fd(char *s, int fd);
void							ft_putchar_fd(char c, int fd);
void							ft_putendl_fd(char *s, int fd);
char							*ft_strjoin(char const *s1, char const *s2);
char							*ft_strcat(char *dest, const char *src);
char							*ft_strcat(char *dest, const char *src);
int								ft_strcmp(const char *s1, const char *s2);
char							*ft_strndup(const char *s, size_t n);
char							*ft_strcpy(char *dest, const char *src);
char							*ft_strncpy(char *dest, const char *src,
									size_t n);
void							ft_bzero(void *s, size_t n);
char							*ft_itoa(int n);
int								ft_isalnum(int c);
char							*ft_substr(char const *s, unsigned int start,
									size_t len);
int								ft_strncmp(const char *s1, const char *s2,
									size_t n);
void							*ft_calloc(size_t nmemb, size_t size);
void							*ft_memcpy(void *dest, const void *src,
									size_t n);

t_ast_node						*parse_input(const char *input_line);

void							free_token_list(t_token *token);
t_ast_node						*parse_tokens(t_token *tokens);
t_token							*skip_command_tokens(t_token *t);
t_ast_node						*parse_pipe(t_token **tokens);
t_ast_node						*parse_and(t_token **tokens_ptr);
t_ast_node						*parse_or(t_token **tokens_ptr);
// minishell.h
t_ast_node						*parse_sequence(t_token **pp);
t_ast_node						*parse_or(t_token **pp);
t_ast_node						*parse_and(t_token **pp);
t_ast_node						*parse_pipeline(t_token **pp);

t_ast_node						*parse_command(t_token **pp);
t_ast_node						*parse_tokens(t_token *tokens);

t_ast_node						*create_ast_node(t_node_type type,
									t_command *cmd);
void							free_strv(char **v);
void							free_args_partial(char **args, int count);
int								grow_args(char ***dst, int *cap, int argc);
int								append_plain(t_command *cmd, char *val,
									int *argc, int *cap);
int								append_wildcard(t_command *cmd, char *val,
									int *argc, int *cap);
t_command						*init_command(int *cap);
int								append_any(t_command *cmd, char *val, int *argc,
									int *cap);
t_command						*cmd_fail(t_command *cmd, int argc);
t_command						*create_command(t_token *tokens, int *consumed);
void							add_redirect(t_command *cmd,
									t_redirect_type type, const char *target);
int								is_redir_token(int t);
t_command						*make_command(t_token *tokens);
int								parse_redirections(t_command *cmd,
									t_token **cursor);
t_ast_node						*parse_command(t_token **tokens_ptr);
t_ast_node						*parse_subshell(t_token **pp);
t_ast_node						*parse_command_or_subshell(t_token **pp);
t_ast_node						*free_and_error(t_ast_node *node);
int								is_invalid_pipe_syntax(t_token *token);
t_ast_node						*parse_pipeline_loop(t_token **tokens_ptr,
									t_ast_node *left);
t_ast_node						*parse_first_command(t_token **tokens_ptr);
t_ast_node						*parse_pipeline(t_token **tokens_ptr);
t_ast_node						*parse_or(t_token **tokens_ptr);
t_ast_node						*parse_and(t_token **tokens_ptr);
t_ast_node						*parse_sequence(t_token **tokens_ptr);
t_ast_node						*parse_tokens(t_token *tokens);

int								expand_ast(t_ast_node *node, t_env_var *env,
									t_shell_context *context);
int								expand_args(char ***pargv, t_env_var *env,
									t_shell_context *context);
int								expand_redirects(t_redirect *r, t_env_var *env,
									t_shell_context *context);
char							*expand_params_keep_quotes(const char *raw,
									t_env_var *env, t_shell_context *context);
int								remove_quotes_inplace(char **ps);
int								had_quote(const char *s);

/* ---- expand utils ---- */
size_t							read_name(const char *s, size_t i);
char							*itoa_status(int n);
char							*pushc(char *s, char c);
char							*pushs(char *s, const char *add);
void							dbg_dump_ast(t_ast_node *n);
int								process_one(t_buildctx *ctx, char *raw,
									t_shell_context *context);
int								strv_count(char **v);
int								handle_wildcard_redir(t_redirect *r, char *noq,
									t_shell_context *context);
char							**grow_out(char **out, int need, int *cap,
									int used);
int								rq_try_open_or_close(int *q, char c, size_t *i);
int								rq_try_dq_escape(const char *s, size_t *i,
									int q, char **out);
int								rq_emit_plain(const char *s, size_t *i,
									char **out);
t_token							*handle_lexer_error(t_token *head,
									char unexpected_char);
int								expand_args(char ***pargv, t_env_var *env,
									t_shell_context *context);
int								rebuild_args(char ***pargv, char **src,
									t_env_var *env, t_shell_context *context);
char							*join_path(const char *dir, const char *cmd);

#endif
