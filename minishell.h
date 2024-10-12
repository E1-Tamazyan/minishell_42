/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 14:42:32 by etamazya          #+#    #+#             */
/*   Updated: 2024/10/12 10:51:26 by etamazya         ###   ########.fr       */
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

// ** init_some_tokenss

typedef enum s_token_type
{
	T_WORD = 0,				// commands and arguments
	T_PIPE = 1,				// '|'
	T_REDIR_IN = 2,			// '<'
	T_REDIR_OUT = 3,		// '>'
	T_REDIR_APPEND = 4,		// '>>'
	T_REDIR_HEREDOC = 5,	// '<<'
	T_ENV_VAR = 6,			// environment variables
	T_QUOTES = 7,			// ""''
	T_LIMITER = 8,			// '<<' after
}				t_token_type;

typedef struct s_token
{
	char			*context;
	t_token_type	type;
	struct s_token	*next;
}			t_token;



//**************************************
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}			t_env;

typedef struct s_shell
{
	t_token		*tok_lst;
	t_env		*env_lst;
	int			shlvl; // check
	char		pwd; // check
	char		*oldpwd; // check
}			   t_shell;
//**************************************

// ***_____main_functions_____***
int		init_input(char *input, t_shell *gen, char **env);
int		check_input(char **env, char *input, t_shell *general);
t_env	*init_env_nodes(char **env);
// // void    *check_db_quote(char *str);

// ***____env_sorting_____***
char    **sort_env(char **env);
void    quick_sort(char **arr, int low, int high);
int     partition(char **arr, int low, int high);
void    swap(char **a, char **b);

// ***_____utils_____***
void    print_env(t_env *lst, int flag);
void	put_key(t_env *node, char	*src);
void	put_value(t_env *node, char *src);
int		sgmnt_len(const char *str, int *pos);
void	print_tokens(t_token *head);
void	my_list_iter(t_token* head);

// ***_____lib utils_____***
void	ft_strlcpy(char *dest, const char *src, int size, int pos);
t_env   *ft_lstnew(char *context);
void    ft_lstadd_back(t_env **lst, t_env *node);
int	    ft_strcmp(const char *s1, const char *s2);
int		ft_strlen(const char *str);
// char	*ft_substr(char const *s, unsigned int start, int len);

// ***_____tokenization_____***

short	init_tokens(const char *input, t_shell *general);
int		count_tokens(const char *s);
char	**split_tokens(const char *s);
int		check_quotes(const char *input, int i);
int		check_sgl_quote(const char *input, int *i);
int		check_symbols(const char *input, int i);

// ** additional
void	printStrings(char **strings);
// int	check1(char c);
// char	*init_some_tokens(int len, char **s);
// char	*cut2(char **s, int *len);
// int	fill_tokens_single_quotes(char *s, int len, int flag);
// int	fill_tokens_quotes(int len, char *s);
// static int	fill_tokens(char **arr, char *s, int i, int len);
// int	single_quote(char *s, int i, int flag2);
// int	if_double(int i, int *count, int *flag, char *s);


#endif