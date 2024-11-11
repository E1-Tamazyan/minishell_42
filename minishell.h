/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 14:42:32 by etamazya          #+#    #+#             */
/*   Updated: 2024/11/11 16:19:02 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H

// # include <std.h> // exit(),
# include <stdio.h> // readline(), perror()
# include <stdlib.h> // exit(),
# include <unistd.h> // fork(), access(),
# include <readline/readline.h> // rl_clear_history(), rl_on_new_line(), rl_replace_line(), rl_redisplay(), 
# include <readline/history.h> // rl_clear_history(), add_history(),
# include <sys/wait.h> // wait(), waitpid(), wait3(), 
# include <sys/resource.h> // (struct rusage *rusage), 
# include <signal.h> //signal(), 

typedef enum s_ttype
{
	T_WORD = 0,				// commands and arguments
	T_PIPE = 1,				// '|'
	T_REDIR_IN = 2,			// '<'
	T_REDIR_OUT = 3,		// '>'
	T_REDIR_APPEND = 4,		// '>>'
	T_REDIR_HEREDOC = 5,	// '<<'
	T_ENV_VAR = 6,			// environment variables
	T_SGL_QUOTES = 7,		// ''
	T_DBL_QUOTES = 8,		// ""
}				t_ttype;

typedef struct s_token
{
	char			*context;
	t_ttype			type;
	struct s_token	*next;
}			t_token;

//**************************************
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}			t_env;

typedef struct s_cmd_token
{
	char	*content;
	t_ttype	*type;
	int		flag;
}			    t_cmd_token;

typedef struct s_shell
{
	t_token		*tok_lst;
	t_env		*env_lst;
	t_env		*sorted_env_lst; //for export, to not change the original env_lst above
	int			shlvl; // check
	// char		pwd; // check
	// char		*oldpwd; // check
}			   t_shell;
//**************************************

// ***_____main_functions_____***
int		init_input(char *input, t_shell *gen, char **env);
int		check_cmd(char **env, t_shell *general);
t_env	*init_env_nodes(char **env);

// ***____env_sorting_____***
char    **sort_env(char **env);
void    quick_sort(char **arr, int low, int high);
int     partition(char **arr, int low, int high);
void    swap(char **a, char **b);

// ***_____utils_____***
void    print_env(t_env *lst, int flag);
void	print_tokens(t_token *head);
int		put_key(t_env *node, char	*src);
void	put_value(t_env *node, char *src, int pos);
int		sgmnt_len(const char *str, int pos);
void	my_list_iter(t_token *head);
int		check_print_dollar(const char *context, t_env *env_lst, int i);
int		create_env(char **env, t_shell *general);
t_token	*optimize_tokens(&general->tok_lst);


// ***_____lib utils_____***
void	ft_strlcpy(char *dest, const char *src, int size, int pos, char limiter);
t_env   *ft_lstnew(char *context);
void    ft_lstadd_back(t_env **lst, t_env *node);
int	    ft_strcmp(const char *s1, const char *s2);
int		ft_strlen(const char *str);
char	*my_substr(const char *s, unsigned int start, int len);
int		ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);

// ***_____tokenization_____***
short	init_tokens(const char *input, t_shell *general, int i);
int		init_op_token(const char *input, int i, t_token *token_list);
void	add_token_list(t_token **list, char *content, t_ttype type);
t_token	*create_token(char *content, t_ttype type);

// ** additional
void	printStrings(char **strings);
int		new_check_quotes(const char *input, int i, t_shell *general);
int		new_check_sgl_quote(const char *input, int i, t_shell *general);
void	clean_list(t_token **list);
void	clean_env_list(t_env **list);


// **************
// archive
char	*ft_substr(char const *s, unsigned int start, int len);
 // void    *check_db_quote(char *str);
// int		new_check_sgl_quote(const char *input, int i, t_token *t_list);
// int		count_tokens(const char *s);
// char	**split_tokens(const char *s);
// int		check_quotes(const char *input, int i);
// int		check_sgl_quote(const char *input, int *i);
// int		check_symbols(const char *input, int i);
// short	my_check_quotes(const char *input, t_token **token_list, int i, int flag);
// int		check1(char c);
// char		*init_some_tokens(int len, char **s);
// char		*cut_quote(char **s, int *len);
// int		fill_t_sgl_quotes(char *s, int len, int flag);
// int		fill_t_dbl_quotes(int len, char *s);
// int		fill_tokens(char **arr, char *s, int i, int len);
// int		single_quote(char *s, int i, int flag2);
// int		if_double(int i, int *count, int *flag, char *s);

#endif