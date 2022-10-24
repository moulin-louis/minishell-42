/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_setup_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:42:25 by loumouli          #+#    #+#             */
/*   Updated: 2022/10/24 15:45:08 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <string.h>

void	clean_lst_mode(t_tok *dest, t_tok *temp, t_tok **lst, int i)
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

void	in_redir(t_tok **lst, t_tok *dest, t_cati *node, t_cati **mini)
{
	t_tok	*temp;

	temp = 0;
	if (ut_strcmp((*lst)->str, dest->str))
	{
		node->infile = ut_strdup((*lst)->next->str);
		if (!node->infile)
			ut_clean_parsing_n_quit(mini, lst, errno);
		node->in_file = 1;
		clean_lst_mode(dest, temp, lst, 1);
		return ;
	}
	temp = *lst;
	while (!ut_strcmp(temp->next->str, dest->str))
		temp = temp->next;
	node->infile = ut_strdup(temp->next->next->str);
	if (!node->infile)
		ut_clean_parsing_n_quit(mini, lst, errno);
	node->in_file = 1;
	clean_lst_mode(dest, temp, lst, 2);
}

void	out_redir(t_tok **lst, t_tok *dest, t_cati *node, t_cati **mini)
{
	t_tok	*temp;

	temp = 0;
	if (ut_strcmp((*lst)->str, dest->str))
	{
		node->outfile = ut_strdup((*lst)->next->str);
		if (!node->outfile)
			ut_clean_parsing_n_quit(mini, lst, errno);
		node->out_trunc = 1;
		clean_lst_mode(dest, temp, lst, 1);
		return ;
	}
	temp = *lst;
	while (!ut_strcmp(temp->next->str, dest->str))
		temp = temp->next;
	node->outfile = ut_strdup(temp->next->next->str);
	if (!node->outfile)
		ut_clean_parsing_n_quit(mini, lst, errno);
	node->out_trunc = 1;
	clean_lst_mode(dest, temp, lst, 2);
}

void	append_redir(t_tok **lst, t_tok *dest, t_cati *node, t_cati **mini)
{
	t_tok	*temp;

	temp = 0;
	if (ut_strcmp((*lst)->str, dest->str))
	{
		node->outfile = ut_strdup((*lst)->next->str);
		if (!node->outfile)
			ut_clean_parsing_n_quit(mini, lst, errno);
		node->out_append = 1;
		clean_lst_mode(dest, temp, lst, 1);
		return ;
	}
	temp = *lst;
	while (!ut_strcmp(temp->next->str, dest->str))
		temp = temp->next;
	node->outfile = ut_strdup(temp->next->next->str);
	if (!node->outfile)
		ut_clean_parsing_n_quit(mini, lst, errno);
	node->out_append = 1;
	clean_lst_mode(dest, temp, lst, 2);
}
