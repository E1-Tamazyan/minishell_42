// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   mini_utils.c                                       :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/08/12 15:29:05 by etamazya          #+#    #+#             */
// /*   Updated: 2024/09/18 22:21:25 by etamazya         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "minishell.h"

// ************************
// *** WARNING *** FULL ***
// ************************

//5 functions already

void put_key(t_env *node, char	*src)
{
	int	i;
	int	j;

	i = 0;
    j = 0;
    while (src[j] && src[j] != '=')
            j++;
    node -> key = (char *)malloc(sizeof(char) * (j + 1));
    if (!node-> key)
        return ;
    ft_strlcpy(node-> key, (const char *)src, (j + 1), 0);
    if (!node-> key)
        return ;
}

void put_value(t_env *node, char *src)
{
	int	i;
	int	n;
	int	pos;
	int	counter;

	i = 0;
	counter = 0;
	while (src[i] && src[i] != '\0')
	{
		n = sgmnt_len((const char *)src, &pos);
		if (n == -1)
			return ;
		node -> value = (char *)malloc(sizeof(char) * n);
        if (!node -> value)
			return ;
        ft_strlcpy(node -> value, src, n, pos);
        if (!node -> value)
            return ;
        i++;
	}
}

void    print_env(t_env *lst, int flag)
{
    if (!lst)
        return ;
	while (lst)
	{
        if (flag == 1)
            printf("declare -x %s\"%s\"\n", lst -> key, lst -> value);
        else
            printf("%s%s\n", lst -> key, lst -> value);
		lst = lst->next;
	}
}

int	sgmnt_len(const char *str, int *pos)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	if (!str)
		return (-1);
	while (str[i] != '=')
		i++;
	if (str[i] == '=') // only once
		i++;
	*pos = i;
	while (str[i] != '\0')
	{
		i++;
		counter++;
	}
	return (counter);
}

void print_tokens(t_token *head)
{
    t_token *current; 

	current = head;
    while (current != NULL)
	{
        // printf("context: %s\n, Type: %d\n", current->context, current->type);
        current = current->next;
    }
}