/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_check_tok.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 14:23:28 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/06 14:33:34 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

/*Ugly function to check if there is a < > in my linked list of token*/

void	check_double_redirection(t_tok **lst, t_cati **mini)
{
	t_tok	*temp;

	temp = *lst;
	while (temp)
	{
		if (ut_strcmp(temp->str, "<") && (temp->next
				&& ut_strcmp(temp->next->str, ">")))
		{
			printf("shellnado : invalid token syntax near '\\n'\n");
			reset_ressources(lst, mini);
			g_status = 2;
			return ;
		}
		temp = temp->next;
	}
}

void	check_pipe_token(t_tok **lst, t_cati **mini)
{
	t_tok	*temp;

	temp = *lst;
	while (temp)
	{
		if (ut_strcmp(temp->str, "|") && !temp->next)
		{
			printf("shellnado : invalid token syntax near '\\n'\n");
			reset_ressources(lst, mini);
			g_status = 2;
			return ;
		}
		if (ut_strcmp(temp->str, "|") && (temp->next && ut_strcmp(temp->next->str, "|")))
		{
			printf("shellnado : invalid token syntax near '|'\n");
			reset_ressources(lst, mini);
			g_status = 2;
			return ;
		}
		temp = temp->next;
	}
}