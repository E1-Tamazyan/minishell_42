/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:11:43 by etamazya          #+#    #+#             */
/*   Updated: 2024/10/08 12:35:20 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// only 2 functions

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

// char	*ft_substr(char const *s, unsigned int start, int len)
// {
// 	int		i;
// 	int		j;
// 	char	*ptr;

// 	i = 0;
// 	j = 0;
// 	if (!s)
// 		return (NULL);
// 	// if (start >= ft_strlen(s))
// 		// ptr = (char *)malloc((len + 1) * sizeof(char))
// 		// return (ft_strdup(""));
// 	if (len > ft_strlen(s))
// 		len = ft_strlen(s);
// 	ptr = malloc(sizeof(char) * (len + 1));
// 	if (!ptr)
// 		return (NULL);
// 	while (len)
// 	{
// 		ptr[i] = s[start];
// 		i++;
// 		start++;
// 		len--;
// 	}
// 	return (ptr);
// }