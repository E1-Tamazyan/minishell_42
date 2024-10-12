/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:38:08 by algaboya          #+#    #+#             */
/*   Updated: 2024/10/12 20:03:21 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// only intiational functions
//2 functions yet

int	init_input(char *input, t_shell *general, char **env)
{
	input = "";
	while (input)
	{
		input = readline("miniHell: ");
		add_history(input);
		if (!input)
			return (1);
		init_tokens((const char *)input, general);
		//check this part later return value and it's influence on check input function
		// if (check_input(env, (const char *)input, general))
		if (check_input(env, input, general))
				return (free(input), 1);
//to be continued...
		// general -> pwd = NULL;
		// general -> oldpwd = NULL;
		// general -> shlvl = 0;
		free(input);
	}
    return (0);
}

// make variables for number for export and env for passing it as an argument here
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
    // system("leaks minishell");
    return (list_env);
}

short	init_tokens(const char *input, t_shell *general) //12
{
	char	**str;

	(void)general;
	(void)str;
	//do we need tokens count?????
	str = split_tokens(input);
	if (!str)
		return (-1);
	// printStrings(str);
	return (0);
}

//***************************
//***************************
//***************************