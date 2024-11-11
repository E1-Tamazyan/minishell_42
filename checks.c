/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:41:54 by etamazya          #+#    #+#             */
/*   Updated: 2024/11/11 16:06:13 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 3 function

int check_cmd(char **env, t_shell *general)
{
	t_token	*tmp;
	int		index;

	tmp = general->tok_lst;
	(void)env;
	while (tmp)
	{
		index = ft_strchr((const char *)tmp->context, '$');
		if (index != -1)
		{	
			int j = check_print_dollar(tmp->context, general -> env_lst, (index + 1));
			if (j == -1)
				return(0);
		}
		if (ft_strcmp((const char *)tmp->context, (const char *)"env") == 0)
			return (print_env(general -> env_lst, 0), 0);			
	    else if (ft_strcmp((const char *)tmp->context, (const char *)"export") == 0)
	        return (print_env(general -> sorted_env_lst, 1), 0);
		tmp = tmp->next;
	}
	if (general->env_lst)
		clean_env_list(&general->env_lst);		
    return (0);
}
// check later the error that could ocurr here

void	clean_env_list(t_env **list)
{
	t_env	*temp;
	t_env	*next;

	temp = *list;
	while (temp != NULL)
	{
		next = temp->next;
		free(temp);
		temp = next;
	}
	*list = NULL;
}

int	new_check_quotes(const char *input, int i, t_shell *general)
{
	int start;
	int flag;
	
	if (input[i] && input[i] == '\"')
	{
		flag = 1;
		start = i;
		i += 1;
		while (input[i] && input[i] != '\"')
			i++;
		if (input[i] && input[i] == '\"')
			flag = 0;
		if (!input[i] && flag)
			return (printf("Missing double quote\n"), -1);
		else
			add_token_list(&general->tok_lst, my_substr(input, start, ((i - start) + 1)), 8);
		i += 1;
	}
	else if (input[i] && input[i] == '\'')
		i = new_check_sgl_quote(input, i, general);
	return (i);
}

int new_check_sgl_quote(const char *input, int i, t_shell *general)
{
	int flag;
	int start;
	
	if (input[i] && input[i] == '\'')
	{
		flag = 1;
		start = i;	
		i += 1;
		while (input[i] && input[i] != '\'')
			i++;
		if (input[i] && input[i] == '\'')
			flag = 0;
		if (!input[i] && flag)
			return (printf("Missing single quote\n"), -1);
		else
			add_token_list(&general->tok_lst, my_substr(input, start, ((i - start) + 1)), 8);
		i += 1;
	}
	return (i);
}


// *********** ARCHIVE ***********
// int check_cmd(char **env, t_shell *general)
// {
//     char    **sorted;

// 	// while (general->token)
// 	// 
// 	// do loop on the t_token list and  check every context
//     if (ft_strcmp((const char *)general->tok_lst, (const char *)"env") == 0)
//     {
//         general -> env_lst = init_env_nodes(env);
//         print_env(general -> env_lst, 0);
//         return (0);
//     }
//     else if (ft_strcmp((const char *)input, (const char *)"export") == 0)
//     {
//         sorted = sort_env(env);
//         general -> env_lst = init_env_nodes(sorted);
//         print_env(general -> env_lst, 1);
//         return (0);
//     }
//     // if (ft_strcmp((const char *)general->tok_lst, (const char *)"env") == 0)
//     // {
//     //     general -> env_lst = init_env_nodes(env);
//         // print_env(general -> env_lst, 0);
//     //     return (0);
//     // }
//     // else if (ft_strcmp((const char *)input, (const char *)"export") == 0)
//     // {
//     //     sorted = sort_env(env);
//     //     general -> env_lst = init_env_nodes(sorted);
//     //     print_env(general -> env_lst, 1);
//     //     return (0);
//     // }
//     return (0);
// }