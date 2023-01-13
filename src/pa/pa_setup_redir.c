/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_setup_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:42:25 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/13 12:38:19 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <stdlib.h>

int	check_compliance_file(t_tok *node, t_tok **lst, t_cati **mini)
{
	if (!node)
		return (trigger_error(lst, mini, "\\n"), 1);
	if (!node->str || ft_strlen(node->str) < 2)
		return (1);
	if (node->str[0] == '|')
		return (trigger_error(lst, mini, "|"), 1);
	if (node->str[0] == '<' && node->str[1] != '<')
		return (trigger_error(lst, mini, "<"), 1);
	if (node->str[0] == '<' && node->str[1] == '<')
		return (trigger_error(lst, mini, "<<"), 1);
	if (node->str[0] == '>' && node->str[1] != '>')
		return (trigger_error(lst, mini, ">"), 1);
	if (node->str[0] == '>' && node->str[1] == '>')
		return (trigger_error(lst, mini, ">>"), 1);
	return (0);
}

void	delete_token_redir(t_tok *node, t_tok **lst)
{
	t_tok	*temp;
	t_tok	*temp2;

	if (ut_strcmp(node->str, (*lst)->str))
	{
		temp = (*lst)->next;
		tok_delone(*lst);
		*lst = temp;
		temp = (*lst)->next;
		tok_delone(*lst);
		*lst = temp;
		return ;
	}
	temp = *lst;
	while (ut_strcmp(temp->next->next->str, node->str))
		temp = temp->next;
	temp2 = temp->next->next;
	tok_delone(temp->next);
	temp->next = temp2;
	if (temp->next->next)
		temp2 = temp->next->next;
	else
		temp2 = NULL;
	tok_delone(temp->next);
	temp->next = temp2;
}

void	in_redir(t_tok *r_token, t_cati *c_node, t_tok **lst, t_cati **mini)
{
	if (check_compliance_file(r_token->next, lst, mini) == 1)
		return ;
	if (c_node)
	{
		if (c_node->infile)
			free(c_node->infile);
		c_node->infile = ut_strdup(r_token->next->str);
		if (!c_node->infile)
			ut_clean_parsing_n_quit(mini, lst, errno);
		check_file(c_node->infile, c_node, lst, mini);
		c_node->in_file = 1;
	}
	delete_token_redir(r_token, lst);
}

void	out_redir(t_tok *r_token, t_cati *c_node, t_tok **lst, t_cati **mini)
{
	if (check_compliance_file(r_token->next, lst, mini) == 1)
		return ;
	if (c_node)
	{
		if (c_node->outfile)
			free(c_node->outfile);
		c_node->outfile = ut_strdup(r_token->next->str);
		if (!c_node->outfile)
			ut_clean_parsing_n_quit(mini, lst, errno);
		check_file(c_node->outfile, c_node, lst, mini);
		c_node->out_trunc = 1;
	}
	delete_token_redir(r_token, lst);
}

void	app_redir(t_tok *r_token, t_cati *c_node, t_tok **lst, t_cati **mini)
{
	if (check_compliance_file(r_token->next, lst, mini) == 1)
		return ;
	if (c_node)
	{
		if (c_node->outfile)
			free(c_node->outfile);
		c_node->outfile = ut_strdup(r_token->next->str);
		if (!c_node->outfile)
			ut_clean_parsing_n_quit(mini, lst, errno);
		check_file(c_node->outfile, c_node, lst, mini);
		c_node->out_append = 1;
	}
	delete_token_redir(r_token, lst);
}
