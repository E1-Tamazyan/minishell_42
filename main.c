/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 14:42:13 by etamazya          #+#    #+#             */
/*   Updated: 2024/09/10 19:00:55 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void take_input(char **input, char **argv)
{
    // char    *p;
    // int count;
    // char    **str;
    (void)argv;
    
    // p = NULL;
    *input = readline("CMD: ");
    if (!*input)
        return ;
    add_history(*input);
    // check_db_quote(input);
    // str = check_db_quote();
}

int check_db_quote(char *str)
{
    size_t  i;
    size_t  count;
    char    *p_to_start;
    // char    *p_to_end;

    i = 0;
    count = 0;
    p_to_start = NULL;
    while (*str != '\0')
    {
        if (*str == 34) // "
            *p_to_start = &str;
        if(*str == 39) // '
        printf("pointer = %s , p = %p\n", p_to_start, p_to_start);
    }
    return (count);
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    (void)envp;
    char *input;

    take_input(&input, argv);
    printf("dsfs = %s\n", input);
    return (0);
}


// main for env vars
// int main(int argc, char **argv, char **envp)
// {
//     (void)argc;
//     (void)argv;
//     (void)envp;
//     char *str;

//     str = malloc(sizeof(char) * 10);
//     if(!str)
//         return (1);
//     printf("hello = %s\n", argv[1]);
//     str = readline();
//     printf("*%s\n", str);
//     // if (argc > 1)
//     //     my_exit("Cannot take any argument");
        
//     // printf("\nEnvironment variables:\n");
//     // for (char **env = envp; *env != 0; env++)
//     //     printf("%s\n", *env);
//     // return 0;
// }