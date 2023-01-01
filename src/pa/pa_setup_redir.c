/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_setup_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:42:25 by loumouli          #+#    #+#             */
/*   Updated: 2022/12/14 12:37:42 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <stdio.h>

int	check_compliance_file(char *str)
{
	if (!str && ft_strlen(str) < 2)
		return (1);
	if (str[0] == '<' && str[1] != '<')
		return (printf("shellnado : invalid token syntax near '<'\n"), 1);
	if (str[0] == '<' && str[1] == '<')
		return (printf("shellnado : invalid token syntax near '<<'\n"), 1);
	if (str[0] == '>' && str[1] != '>')
		return (printf("shellnado : invalid token syntax near '>'\n"), 1);
	if (str[0] == '>' && str[1] == '>')
		return (printf("shellnado : invalid token syntax near '>>'\n"), 1);
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
	if (!r_token->next)
	{
		printf("shellnado : invalid token syntax near '\\n'\n");
		g_status = 2;
		reset_ressources(lst, mini);
		return ;
	}
	if (check_compliance_file(r_token->next->str))
	{
		reset_ressources(lst, mini);
		g_status = 2;
		return ;
	}
	c_node->infile = ut_strdup(r_token->next->str);
	if (!c_node)
		ut_clean_parsing_n_quit(mini, lst, errno);
	c_node->in_file = 1;
	delete_token_redir(r_token, lst);
}

void	out_redir(t_tok *r_token, t_cati *c_node, t_tok **lst, t_cati **mini)
{
	if (!r_token->next)
	{
		printf("shellnado : invalid token syntax near '\\n'\n");
		g_status = 2;
		reset_ressources(lst, mini);
		return ;
	}
	if (check_compliance_file(r_token->next->str))
	{
		reset_ressources(lst, mini);
		g_status = 2;
		return ;
	}
	c_node->outfile = ut_strdup(r_token->next->str);
	if (!c_node)
		ut_clean_parsing_n_quit(mini, lst, errno);
	c_node->out_trunc = 1;
	delete_token_redir(r_token, lst);
}

void	app_redir(t_tok *r_token, t_cati *c_node, t_tok **lst, t_cati **mini)
{
	if (!r_token->next)
	{
		printf("shellnado : invalid token syntax near '\\n'\n");
		g_status = 2;
		reset_ressources(lst, mini);
		return ;
	}
	if (check_compliance_file(r_token->next->str))
	{
		reset_ressources(lst, mini);
		g_status = 2;
		return ;
	}
	c_node->outfile = ut_strdup(r_token->next->str);
	if (!c_node)
		ut_clean_parsing_n_quit(mini, lst, errno);
	c_node->out_append = 1;
	delete_token_redir(r_token, lst);
}
