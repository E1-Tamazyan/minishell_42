/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:41:54 by etamazya          #+#    #+#             */
/*   Updated: 2024/10/26 18:54:48 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 2 function

int check_input(char **env, char *input, t_shell *general)
{
    char    **sorted;

    if (ft_strcmp((const char *)input, (const char *)"env") == 0)
    {
        general -> env_lst = init_env_nodes(env);
        print_env(general -> env_lst, 0);
        return (0);
    }
    else if (ft_strcmp((const char *)input, (const char *)"export") == 0)
    {
        sorted = sort_env(env);
        general -> env_lst = init_env_nodes(sorted);
        print_env(general -> env_lst, 1);
        return (0);
    }
    // to be continued...
    return (0);
}

int	init_op_token(const char *input, int i, t_token *token_list)
{
	// printf("v=barevvvv\n");
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

int	new_check_quotes(const char *input, int i, t_token *t_list)
{		
	int closing_quote;
	int flag;

	flag = 0;
	closing_quote = 0;
	(void)t_list;
	while (input[i])
	{
		if (input[i] == 34)
		{
			flag = 1;
			while (input[i] && input[++i] && input[i] != 34) // && input[i + 1] == ' ' // consider later
				flag = 0;
			if (!input[i] && flag == 0)
				return (printf("Missing double quote\n"), -1);
			else
				closing_quote = i;
			printf("*** = %d\n", closing_quote);
		}
		// what to do to get out of here
		if (input[i] == 39)
		{
			i = new_check_sgl_quote(input, i, t_list);
			if (i == -1)
				return (-1);
		}
		i++;
	}
	// add_token_list(&token_list, my_substr(input, i, 1), 1);
	// here should be add_token_list with create_token function;
	printf("bye_quote\n");
	return (i);
}

int new_check_sgl_quote(const char *input, int i, t_token *t_list)
{
	int flag;
	int closing_quote;

	flag = 0;
	closing_quote = 0;
	(void)t_list;
	while (input[i])
	{
		if (input[i] == 39)
		{
			flag = 1;
			while (input[i] && input[++i] && input[i] && input[i] != 39) // && input[i + 1] == ' ' // consider later
				flag = 0;
			printf("***> input[i] = %c, %d\n", input[i], i);
			if (!input[i])
				return (printf("Missing single quote\n"), -1);
			else
				closing_quote = i;
		}
		i++;
	}
	// here should be add_token_list with create_token function;
	printf("bye_single_quote\n");
	return (i);
}
