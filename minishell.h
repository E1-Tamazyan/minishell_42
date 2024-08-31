/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 14:42:32 by etamazya          #+#    #+#             */
/*   Updated: 2024/08/31 16:58:53 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h> // readline(), perror()
# include <stdlib.h> // exit(),
# include <unistd.h> // fork(), access(),
# include <readline/readline.h> // rl_clear_history(), rl_on_new_line(), rl_replace_line(), rl_redisplay(), 
# include <readline/history.h> // rl_clear_history(), add_history(),
# include <sys/wait.h> // wait(), waitpid(), wait3(), 
# include <sys/resource.h> // (struct rusage *rusage), 
# include <signal.h> //signal(), 

void    my_exit(char *msg);
void    take_input(char **input, char **argv);

//void (*signal(int signum, void (*handler)(int)))(int);

#endif