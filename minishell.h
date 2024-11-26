/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 14:42:32 by etamazya          #+#    #+#             */
/*   Updated: 2024/11/24 19:33:24 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

// # include <std.h> // exit(),
#include <stdio.h>			   // readline(), perror()
#include <stdlib.h>			   // exit(),
#include <unistd.h>			   // fork(), access(),
#include <readline/readline.h> // rl_clear_history(), rl_on_new_line(), rl_replace_line(), rl_redisplay(),
#include <readline/history.h>  // rl_clear_history(), add_history(),
#include <sys/wait.h>		   // wait(), waitpid(), wait3(),
#include <sys/resource.h>	   // (struct rusage *rusage),
#include <signal.h>			   //signal(),

typedef enum s_ttype
{
	WORD = 0,			 // commands and arguments
	PIPE = 1,			 // '|'
	REDIR_IN = 2,		 // '<'
	REDIR_OUT = 3,	 	// '>'
	REDIR_APPEND = 4,	 // '>>'
	REDIR_HEREDOC = 5, // '<<'
	ENV_VAR = 6,		 // ENV
	QUOTES = 7,		 // "" ''
	// T_SGL_QUOTES = 7, // ''
	// T_DBL_QUOTES = 8, // ""
} t_ttype;

typedef struct s_token
{
	char *context;
	t_ttype type;
	struct s_token *next;
} t_token;

//**************************************
typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
} t_env;


// typedef struct s_cmd_token
// {
// 	char	*content;
// 	char	*type;
// 	t_ttype	*type;
// 	int		flag;
// 	int		quote_type;
// } t_cmd_token;

typedef struct s_cmd_lst
{
	size_t	index;
	char	*content;
	char	**args;
// 	pid_t pid;
// 	// t_descriptor *descriptors;

}			t_cmd_lst;

// ************************
// ************************
// **************** ARCHIVE
// ************************

// struct				s_cmd
// {
// 	t_shell *shell;
// 	char *name;
// 	char *orig_name;
// 	t_list *options;
// 	t_list *args;		//here was an attribute deprecated

// 	t_list *tokens;

// 	int redirection;
// };

// struct				s_cmd_container
// {
// 	t_shell			*shell;
// 	t_cmd		**arr;
// 	size_t			size;
// 	size_t			current_cmd_index;
// 	t_fd			*fds;
// 	t_list 		 	*tokens;
// };

// ************************
// ************************

// typedef enum e_token_type
// {
// 	WORD,
// 	S_PIPE,
// 	D_PIPE,
// 	S_AND,
// 	D_AND,
// 	D_QUOTE,
// 	S_QUOTE,
// 	IN_REDIR,
// 	OUT_REDIR,
// 	HERE_DOC,
// 	APPEND_REDIR,
// 	ERROR,
// 	NONE,
// 	FILEIN,
// 	LIMITER,
// 	FILEOUT,
// 	APPEND_FILEOUT
// }	t_token_type;

// typedef struct s_split
// {
// 	char			*value;
// 	t_token_type	type;
// 	struct s_split	*next;
// }	t_split;

// typedef struct s_dollar_var
// {
// 	char	*str;
// 	int		i;
// 	int		is_dquote;
// 	int		is_squote;
// }	t_dollar_var;

// typedef struct s_env
// {
// 	char	*var;
// 	char	*value;
// 	t_env	*next;
// }	t_env;

// typedef struct s_quote_var
// {
// 	int		j;
// 	int		in_single_quote;
// 	int		in_double_quote;
// }	t_quote_var;

// typedef struct s_merge_var
// {
// 	int		n1;
// 	int		n2;
// 	int		k;
// 	int		i;
// 	int		j;
// 	char	**l;
// 	char	**r;
// 	char	**arr;
// }	t_merge_var;

// typedef struct s_vars
// {
// 	int		start;
// 	int		end;
// 	int		flag;
// 	char	*input;
// 	char	current_quote;
// }	t_vars;

// typedef struct s_minishell
// {
// 	t_split	*tokens;
// 	t_env	*env;
// 	int		(*fd)[2];
// 	int		fd_in;
// 	int		fd_out;
// 	int		fd_heredoc;
// 	int		is_builtin;
// 	int		file_err;
// 	int		pipes;
// 	pid_t	*pid;
// 	char	**cmd;
// }	t_minishell;

// ************************
// **************** ARCHIVE
// ************************
// ************************

// ### NOW WORKING ###

typedef struct s_dollar
{
	char *u_key;
	char *value;
	int	dollar_sign; // 1 = sgl_quote, 2 = dbl quote
	struct s_dollar	*next;

}	t_dollar;

typedef struct s_shell
{
	t_token		*tok_lst;
	t_env		*env_lst;
	t_cmd_lst	*cmd_list;
	t_dollar	*doll_lst;
	t_env		*sorted_env_lst; // for export, to not change the original env_lst above
	int			shlvl;		     // check
	// char		pwd; // check
	// char		*oldpwd; // check
} t_shell;

// ### NOW WORKING ###

//**************************************

// ***_____main_functions_____***
int init_input(char *input, t_shell *gen, char **env);
int check_cmd(char **env, t_shell *general);
t_env *init_env_nodes(char **env);

// ***____env_sorting_____***
char **sort_env(char **env);
void quick_sort(char **arr, int low, int high);
int partition(char **arr, int low, int high);
void swap(char **a, char **b);

// ***_____utils_____***
void print_env(t_env *lst, int flag);
void print_tokens(t_token *head);
int put_key(t_env *node, char *src);
void put_value(t_env *node, char *src, int pos);
int sgmnt_len(const char *str, int pos);
// void	my_list_iter(t_token *head);
int check_print_dollar(const char *context, t_env *env_lst, int i);
int create_env(char **env, t_shell *general);
t_cmd_lst	*exchange_to_commands(t_token *tok_lst, t_shell *general);

// ***_____lib utils_____***
void ft_strlcpy(char *dest, const char *src, int size, int pos, char limiter);
t_env *ft_lstnew(char *context);
void ft_lstadd_back(t_env **lst, t_env *node);
int ft_strcmp(const char *s1, const char *s2);
int ft_strlen(const char *str);
char *my_substr(const char *s, unsigned int start, int len);
int ft_strchr(const char *s, int c);
char *ft_strdup(const char *s1);
char *ft_strjoin(char *s1, char *s2);

// ***_____tokenization_____***
short	init_tokens(const char *input, t_shell *general, int i);
int		init_op_token(const char *input, int i, t_token **token_list);
void	add_token_list(t_token **list, char *content, t_ttype type);
t_token	*create_token(char *content, t_ttype type);

// ** additional
void	printStrings(char **strings);
void	clean_list(t_token **list);
void	clean_env_list(t_env **list);
short	del_t_node(t_token *lst);
int		check_cut_quotes(const char *input, int start, int i, t_shell *general);

// **************
int	check_dollar_sign(char *input, int i, t_shell *general);

// archive
char *ft_substr(char const *s, unsigned int start, int len);

#endif