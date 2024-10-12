/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:18:12 by etamazya          #+#    #+#             */
/*   Updated: 2024/10/12 19:44:47 by etamazya         ###   ########.fr       */
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

int	count_tokens(const char *input)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	//mandatory lines ⏬ ®
	while (input[i] != '\0')
	{
		j = check_quotes(input, i);
		if (j == -1)
			return (-1);
		i = j;
		i++;
		if (check_symbols(input, i) == -1)
			return (-1);
	}
	return (i);
}

char	**split_tokens(const char *input)
{
	int		count;
	char	**str;

	count = 0;
	if (input)
	{
		count = count_tokens(input);
		if (count == -1)
			return (NULL);
	}
	str = malloc((count + 1) * sizeof(char *));
	if (!str)
		return (0);
	str[count] = NULL;
	// if (count > 0)
		//make tokens list;
	return (str);
}
