/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:41:54 by etamazya          #+#    #+#             */
/*   Updated: 2024/10/12 19:43:15 by etamazya         ###   ########.fr       */
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

int check_symbols(const char *input, int i)
{
    // if (input[i] == '\0' && (input[i] == ' ' || input[i] == '|'
    //     || input[i] == '<' || input[i] == '>'))
    // {
    //     i++;
    //     if (input[i + 1] != '\0' && (input[i] == ' ' || input[i] == '|'
    //     || input[i] == '<' || input[i] == '>'))
    //         i++;
    // }
    return (i);
}