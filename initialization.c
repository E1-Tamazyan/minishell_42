/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:38:08 by algaboya          #+#    #+#             */
/*   Updated: 2024/11/20 16:57:10 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// only intiational functions
// 5 functions already

// ***************************
// ****** WARNING FULL *******
// ***************************


int	init_input(char *input, t_shell *general, char **env)
{
	input = "";
	while (input)
	{
		create_env(env, general);
		input = readline("\033[38;5;51m\033[48;5;16m minisHell:\033[0m "); //neon
		// input = readline("\033[38;5;175m\033[48;5;153m minisHell:\033[0m "); // Pastel Theme
		// input = readline("\033[38;5;129m\033[48;5;233m minisShell:\033[38;5;81m\033[0m "); //bright purples and blues with a dark background 
		// input = readline("\033[38;5;51m\033[48;5;16m minisShell:\033[0m "); // cyan neon
		add_history(input);
		if (!input)
			return (1);
		// init_general(general) // give every value of struct to it's corresponding one
		general -> tok_lst = NULL;
		init_tokens((const char *)input, general, 0);
		print_tokens(general->tok_lst);
		if (check_cmd(env, general)) // if 1 error
			return (free(input), clean_list(&general->tok_lst), 1);
		clean_list(&general->tok_lst);
		free(input);
	}
	printf("exit\n");
    return (0);
}

t_env *init_env_nodes(char **env) 
{
    t_env	*list_env;
    t_env	*tmp;
	t_env	*new_node;
    int i;

	i = 0;
	list_env = NULL;
	tmp = NULL;
    while (env[i] != NULL) 
	{
        new_node = ft_lstnew(env[i]);
        if (!new_node) 
            return NULL;
		if (list_env == NULL) 
		{
            list_env = new_node;
            tmp = list_env;
        }
		else
            ft_lstadd_back(&tmp, new_node);
        i++;
    }
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
				&& input[i] != ' ' && input[i] != 34 && input[i] != 39)
				i++;
			if (i > start)
				add_token_list(&general->tok_lst, my_substr(input, start, i - start), 0);
			i--;
		}
		if(i < 0)
			return (clean_list(&general->tok_lst), -1);
		i++;
	}
	// print_tokens(general->tok_lst);
	general->tok_lst = optimize_tokens(general->tok_lst);
	printf("***second_part***\n");
	print_tokens(general->tok_lst);
	return (0);
}
// | > >> < << ' ' everything beside this are considered command
t_token	*optimize_tokens(t_token *tok_lst)
{
	int	type;
	t_token	*tmp;
	t_token	*head;

	(void)type;
	tmp = tok_lst;
	head = tmp;
	while (tmp)
	{
		if ((tmp -> type == 6 && tmp->next && tmp->next->type == 6)
			|| (tmp -> type == 0 && tmp->next && tmp->next->type == 0)
			|| (tmp -> type == 8 && tmp->next && tmp->next->type == 8))
		{
			// at first we copy the context, then checking the type and then changing the address
			tmp->context = ft_strjoin(tmp->context, tmp->next->context);
			if (!tmp->context)
				return (NULL);
			if (del_t_node(tmp) == -1)
				return (NULL);
		}
		tmp = tmp -> next;
	}
	tmp = head;
	
	print_tokens(tmp);
	return (tok_lst); // still this is okayy
}

short del_t_node(t_token *lst)
{
    t_token *tmp;

    if (lst == NULL || lst->next == NULL)
        return (-1);
    tmp = lst->next;
	lst->next = tmp->next;
    // lst->next = lst->next->next;
    free(tmp->context);
    free(tmp);
    return (0);
}

int	init_op_token(const char *input, int i, t_token *token_list)
{
	if (input[i] && input[i] == '|')
		add_token_list(&token_list, my_substr(input, i, 1), 1);
	else if (input[i] && input[i] == ' ')
	{
		add_token_list(&token_list, my_substr(input, i, 1), 0);
		while (input[i] == ' ')
			i++;
		i -= 1;
	}
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

int create_env(char **env, t_shell *general)
{
	char    **sorted;

	general -> env_lst = init_env_nodes(env);
	sorted = sort_env(env);
	general -> sorted_env_lst = init_env_nodes(sorted);
	return (0);
}