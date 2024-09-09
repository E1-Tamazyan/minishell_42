/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 14:42:13 by etamazya          #+#    #+#             */
/*   Updated: 2024/09/09 17:49:46 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void take_input(char **input, char **argv)
{
    (void)input;
    (void)argv;

    printf("take input\n");
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    (void)envp;
    char *input;

    take_input(&input, argv);
    while ((input = readline("Enter command: ")) != NULL)
    {
        if (*input)
            add_history(input);
        printf("Input: %s\n", input);
        free(input);
    }
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