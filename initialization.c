/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:38:08 by algaboya          #+#    #+#             */
/*   Updated: 2024/10/26 16:37:55 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// only intiational functions
// 3 functions yet

int	init_input(char *input, t_shell *general, char **env)
{
	input = "";
	(void)env;
	while (input)
	{
		input = readline("\033[105;78;15;201m minisHell:\033[0:000m "); // magenta = [38;5;201m | cyan [38;5;51m
		add_history(input);
		if (!input)
			return (1);
		general -> tok_lst = NULL;
		init_tokens((const char *)input, general);
		// print_tokens(general->tok_lst); // additional fucntion
//het berel heto // if (check_input(env, input, general))
//het berel heto //return (free(input), clean_list(general->tok_lst), 1);
		// general -> pwd = NULL;
		// general -> oldpwd = NULL;
		clean_list(&general->tok_lst);
		free(input);
	}
    return (0);
}

// make variables for number of export and env for passing it as an argument here
t_env *init_env_nodes(char **env)
{
    t_env   *list_env;
    t_env   *tmp;
    int     i;

    i = 0;
    list_env = NULL;
    tmp = list_env;
    list_env = ft_lstnew(env[i]);
    if (!list_env)
        return (NULL);
    i = 0;
    tmp = list_env;
    while (env[i] != '\0')
    {
        ft_lstadd_back(&list_env, ft_lstnew(env[i]));
        i++;
    }
    list_env = tmp;
    return (list_env);
}

short	init_tokens(const char *input, t_shell *general)
{
	int	i;
	int	start;

	i = 0;
	while ((input[i] >= 9 && input[i] <= 13) || input[i] == 32)
		i++;
	while (input[i] && input[i] != '\0')
	{
		i = new_check_quotes(input, i, general->tok_lst);
		// printf("***%d\n", __LINE__);
		if (input[i] && (input[i] == '|' || input[i] == ' ' || input[i] == '>'
			|| input[i] == '<'))
				i = init_op_token(input, i, general->tok_lst);
		else
		{
			start = i;
			while (input[i] && input[i] != '|' && input[i] != '>' && input[i] != '<'
				&& input[i] != ' ' && input[i] != '\0')
				i++;
			add_token_list(&general->tok_lst, my_substr(input, start, i - start), 0);
			i--;
		}
		printf("hiiiiiiii\n");
		i++;
	}
	return (0);
}
// str = split_tokens(input); // comment_test
// neovim (neovim config)