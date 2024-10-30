/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:38:08 by algaboya          #+#    #+#             */
/*   Updated: 2024/10/30 17:43:21 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// only intiational functions
// 4 functions already

// ***************************
// ****** WARNING FULL *******
// ***************************

int	init_input(char *input, t_shell *general, char **env)
{
	input = "";
	(void)env;
	while (input)
	{
		// input = readline("\033[105;78;15;201m minisHell:\033[0:000m "); // magenta = [38;5;201m | cyan [38;5;51m
		input = readline("\033[38;5;51m minisHell:\033[0:000m "); // magenta = [38;5;201m | cyan [38;5;51m
		add_history(input);
		if (!input)
			return (1);
		general -> tok_lst = NULL;
		init_tokens((const char *)input, general, 0);
		if (check_input(env, general))
			return (free(input), clean_list(&general->tok_lst), 1);
		clean_list(&general->tok_lst);
		free(input);
	}
	printf("exit\n");
    return (0);
}

t_env *init_env_nodes(char **env)
{
    t_env   *list_env;
    t_env   *tmp;
    int     i;

    i = 0;
    list_env = NULL;
    tmp = list_env;
    list_env = ft_lstnew(env[i]);
	// printf("***iniiiit\n");
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
	// tmp = NULL;
    return (list_env);
}

short	init_tokens(const char *input, t_shell *general, int i)
{
	int	start;

	while ((input[i] >= 9 && input[i] <= 13) || input[i] == 32)
		i++;
	while (input[i] != '\0' && i >= 0)
	{
		if (i >= 0 && (input[i] == 39 || input[i] == 34))
			i = new_check_quotes(input, i, general);
		if (i >= 0 && input[i] && (input[i] == '|' || input[i] == ' ' || input[i] == '>'
			|| input[i] == '<'))
				i = init_op_token(input, i, general->tok_lst);
		else
		{ 
			start = i;
			while (i >= 0 && input[i] && input[i] != '|' && input[i] != '>' && input[i] != '<'
				&& input[i] != ' ' && input[i] != 34 && input[i] != 39 && input[i] != '\0')
				i++;
			add_token_list(&general->tok_lst, my_substr(input, start, i - start), 0);
			i--;
		}
		if(i < 0)
			return (clean_list(&general->tok_lst), -1);
		i++;
	}
	return (0);
}

int	init_op_token(const char *input, int i, t_token *token_list)
{
	if (input[i] && input[i] == '|')
		add_token_list(&token_list, my_substr(input, i, 1), 1);
	else if (input[i] && input[i] == ' ')
		add_token_list(&token_list, my_substr(input, i, 1), 0);
	else if (input[i] && input[i] == '>')
		if (input[i] && input[++i] && input[i] && input[i] == '>')
			return (add_token_list(&token_list, my_substr(input, i - 1, 2), 4), i);
		else
			add_token_list(&token_list, my_substr(input, --i, 1), 3);
	else if (input[i] && input[i] == '<')
	{
		if (input[i] && input[++i] && input[i] && input[i] == '<')
			return (add_token_list(&token_list, my_substr(input, i - 1, 2), 5), i);
		else
			add_token_list(&token_list, my_substr(input, --i, 1), 2);
	}
	return (i);
}