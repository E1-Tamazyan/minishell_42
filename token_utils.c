/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:18:12 by etamazya          #+#    #+#             */
/*   Updated: 2024/10/23 11:10:58 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// **** 3 functions ****

int	check_sgl_quote(const char *input, int *i)
{
	if (input[*i] == '\'')
	{
		*i += 1;
		while (input[*i] && input[*i] != 39)
			*i += 1;
		if (!input[*i])
			return (printf("Missing closing single quote\n"), -1);
	}
	else if (input[*i] == '\'')
		*i += 1;
	return (0);
}

int check_quotes(const char *input, int i)
{
	if (!input)
		return (-1);
	if (input && input[i] == 34)
	{
		i++;
		while (input[i] && input[i] != 34)
			i++;
		if (!input[i])
			return (printf("Missing closing double quote\n"), -1);
	}
	else if (input[i] == 34)
		i++;
	check_sgl_quote(input, &i);
	return (i);
}

// char	**split_tokens(const char *input)
// {
// 	int		count;
// 	char	**str;

// 	count = 0;
// 	if (input)
// 	{
// 		count = count_tokens(input);
// 		if (count == -1)
// 			return (NULL);
// 	}
// 	str = malloc((count + 1) * sizeof(char *));
// 	if (!str)
// 		return (0);
// 	str[count] = NULL;
// 	// if (count > 0)
// 		//make tokens list;
// 	return (str);
// }



void	add_token_list(t_token **list, char *content, t_ttype type)
{
	t_token	*last;
	t_token	*new;

	new = create_token(content, type);
	if (!new)
		return ;
	if (*list == NULL)
	{
		*list = new;
		return ;
	}
	last = *list;
	while (last && last->next)
		last = last->next;
	last->next = new;
}

t_token	*create_token(char *value, t_ttype type)
{
	int		j;
	t_token	*new;

	j = ft_strlen(value);
	new = (t_token *)malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	new->context = my_substr(value, 0, j);
	new->type = type;
	new->next = NULL;
	return (new);
}