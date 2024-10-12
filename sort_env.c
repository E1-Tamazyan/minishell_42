/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 18:24:16 by etamazya          #+#    #+#             */
/*   Updated: 2024/10/06 16:15:36 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void swap(char **a, char **b)
{
    char *temp;
    
    temp = *a;
    *a = *b;
    *b = temp;
}

int partition(char **arr, int low, int high)
{
    char *pivot;
    int i;
    int j;

    pivot = arr[high];
    i = low - 1;
    j = low;
    while (j < high) 
    {
        if (ft_strcmp(arr[j], pivot) < 0)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
        j++;
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quick_sort(char **arr, int low, int high)
{
    int p;

    p = 0;
    if (low < high)
    {
        p = partition(arr, low, high);
        quick_sort(arr, low, p - 1);
        quick_sort(arr, p + 1, high);
    }
}

char    **sort_env(char **env)
{
    int     i;
    
    i = 0;
    while (env[i] && env[i] != '\0')
        i++;
    quick_sort(env, 0, i - 1);

    return (env);
}