/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_setup_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:42:25 by loumouli          #+#    #+#             */
/*   Updated: 2022/10/19 15:58:37 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clean_lst(t_tok *dest, t_tok *temp, t_tok **lst, int i)
{
	if (i == 1)
	{
		temp = (*lst)->next;
		tok_delone((*lst));
		(*lst) = temp;
		temp = (*lst)->next;
		tok_delone((*lst));
		(*lst) = temp;
	}
	else if (i == 2)
	{
		dest = temp->next;
		temp->next = temp->next->next;
		tok_delone(dest);
		dest = temp->next;
		temp->next = temp->next->next;
		tok_delone(dest);
	}
}

void	in_redir(t_tok **lst, t_tok *dest, t_cati *mini)
{
	t_tok	*temp;

	temp = 0;
	if (ut_strcmp((*lst)->str, dest->str))
	{
		mini->infile = ut_strdup((*lst)->next->str);
		if (!mini->infile)
			return ;
		mini->in_file = 1;
		clean_lst(dest, temp, lst, 1);
		return ;
	}
	temp = *lst;
	while (!ut_strcmp(temp->next->str, dest->str))
		temp = temp->next;
	mini->infile = ut_strdup(temp->next->next->str);
	if (!mini->infile)
		return ;
	mini->in_file = 1;
	clean_lst(dest, temp, lst, 2);
}

void	out_redir(t_tok **lst, t_tok *dest, t_cati *mini)
{
	t_tok	*temp;

	temp = 0;
	if (ut_strcmp((*lst)->str, dest->str))
	{
		mini->outfile = ut_strdup((*lst)->next->str);
		if (!mini->outfile)
			return ;
		mini->out_trunc = 1;
		clean_lst(dest, temp, lst, 1);
		return ;
	}
	temp = *lst;
	while (!ut_strcmp(temp->next->str, dest->str))
		temp = temp->next;
	mini->outfile = ut_strdup(temp->next->next->str);
	if (!mini->outfile)
		return ;
	mini->out_trunc = 1;
	clean_lst(dest, temp, lst, 2);
}

void	append_redir(t_tok **lst, t_tok *dest, t_cati *mini)
{
	t_tok	*temp;

	temp = 0;
	if (ut_strcmp((*lst)->str, dest->str))
	{
		mini->outfile = ut_strdup((*lst)->next->str);
		if (!mini->outfile)
			return ;
		mini->out_append = 1;
		clean_lst(dest, temp, lst, 1);
		return ;
	}
	temp = *lst;
	while (!ut_strcmp(temp->next->str, dest->str))
		temp = temp->next;
	mini->outfile = ut_strdup(temp->next->next->str);
	if (!mini->outfile)
		return ;
	mini->out_append = 1;
	clean_lst(dest, temp, lst, 2);
}

void	heredoc_redir(t_tok **lst, t_tok *dest, t_cati *mini)
{
	/*HANDLE HEREDOC*/
}
