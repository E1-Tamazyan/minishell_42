/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:45:48 by etamazya          #+#    #+#             */
/*   Updated: 2024/11/19 20:00:20 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ************************
// *** WARNING *** FULL ***
// ************************
// **5 functions already **

t_env	*ft_lstnew(char *context) // contains blabla = blabla=bla
{
	int	pos;
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	pos = put_key(node, context);	
	put_value(node, context, pos);
	node -> next = NULL;
	return (node);
}

void	ft_lstadd_back(t_env **lst, t_env *node)
{
	t_env	*current;

	if (!lst || !node)
		return ;
	if (!*lst)
	{
		*lst = node;
		return ;
	}
	current = *lst;
	while (current -> next)
		current = current -> next;
	current->next = node;
}

void	ft_strlcpy(char *dest, const char *src, int size, int pos, char limiter)
{
	int	i;

	i = 0;
	while (i < size && src[pos] && src[pos] != limiter)
	{
		dest[i] = src[pos];
		i++;
		pos++;
	}
	dest[i] = '\0';
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;
	int		res;

	i = 0;
	while ((s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
		{
			res = (int)(unsigned char)s1[i] - (int)(unsigned char)s2[i];
			return (res);
		}
		i++;	
	}
	return (0);
}