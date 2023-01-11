/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_check_tok.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 14:23:28 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/10 11:47:09 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	trigger_error(t_tok **lst, t_cati **mini, char *token_error)
{
	printf("shellnado : invalid token syntax near '%s'\n", token_error);
	reset_ressources(lst, mini);
	g_status = 2;
}

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
			trigger_error(lst, mini, "\\n");
			return ;
		}
		temp = temp->next;
	}
}

void	check_pipe_token(t_tok **lst, t_cati **mini)
{
	t_tok	*temp;

	temp = *lst;
	if (ut_strcmp(temp->str, "|"))
	{
		trigger_error(lst, mini, "|");
		return ;
	}
	while (temp)
	{
		if (ut_strcmp(temp->str, "|") && !temp->next)
		{
			trigger_error(lst, mini, "|");
			return ;
		}
		if (ut_strcmp(temp->str, "|") && (temp->next
				&& ut_strcmp(temp->next->str, "|")))
		{
			trigger_error(lst, mini, "|");
			return ;
		}
		temp = temp->next;
	}
}
