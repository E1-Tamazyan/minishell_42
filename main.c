/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 14:42:13 by etamazya          #+#    #+#             */
/*   Updated: 2024/09/09 20:09:07 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void take_input(char **input, char **argv)
{
    // char    *p;
    // int count;
    char    **str;
    (void)argv;
    
    p = NULL;
    *input = readline("Enter command: ");
    if (!*input)
        return ;
    add_history(*input);
    check_db_quote(input);
    str = check_db_quote();
}

int check_db_quote(char *str)
{
    size_t  i;
    size_t  count;
    char    *p;
    char    *p1;

    i = 0;
    count = 0;
    while (*str)
    {
        if (*str == '"')
            count += 1;
        p = str;
        if(count == 2)
            p1 = str;
        printf("hereeee %p, | %s\n", str, p1);
        str++;
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