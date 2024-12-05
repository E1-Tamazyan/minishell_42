/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:11:10 by elen_t13          #+#    #+#             */
/*   Updated: 2024/12/05 18:19:55 by elen_t13         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exchange_to_cmd(t_shell *general)
{
    t_cmd_lst *tmp;
    t_cmd_lst *head;

    tmp = general->cmd_list;
    head = general->cmd_list;
    while (general->tok_lst)
    {
        counter_args(general);
        general->cmd_list->args = (char **)malloc(sizeof(char *) * (general->arg_count + 1))
        
        tok_tmp = tok_tmp -> next;
    }
}

void counter_args(t_tshell *general)
{
    general->args_count = 0;
    while(general->tok_lst)
    {
        if(general->tok_lst->type != 0)
            return ;
        general-> arg_count++;
        general->tok_lst = general->tok_lst->next
    }
}