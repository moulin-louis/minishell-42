/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_check_tok.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 14:23:28 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/13 12:23:40 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	trigger_error(t_tok **lst, t_cati **mini, char *token_error)
{
	ut_putstr_fd("bash: syntax error near unexpected token `", 2);
	ut_putstr_fd(token_error, 2);
	ut_putstr_fd("'\n", 2);
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
