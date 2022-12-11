/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_setup_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:42:25 by loumouli          #+#    #+#             */
/*   Updated: 2022/12/05 21:51:49 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <string.h>
#include <stdio.h>

char *return_op(char *str, t_tok **lst, t_cati **mini)
{
	if (str[0] == '<' && str[1] != '<')
		return ("<");
	if (str[0] == '>' && str[1] != '>')
		return (">");
	if (str[0] == '<' && str[1] == '<')
		return ("<<");
	if (str[0] == '>' && str[1] == '>')
		return (">>");
	if (str[0] == '|')
		return ("|");
	(void)lst;
	(void)mini;
	return (NULL);
}

int	check_compliance_redir(char *str, t_tok **lst, t_cati **mini)
{
	char	*temp;

	temp = return_op(str, lst, mini);
	if (temp)
	{
		printf("shellnado : syntax error near unexpected token '%s'\n", temp);
		clean_tok(lst);
		clean_mini(mini);
		*mini = NULL;
		return (1);
	}
	return (0);
}

/*clean redir node*/

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

/*Handle in redir*/

void	in_redir(t_tok **lst, t_tok *dest, t_cati *node, t_cati **mini)
{
	t_tok	*temp;

	temp = 0;
	if (ut_strcmp((*lst)->str, dest->str))
	{
		if (check_compliance_redir((*lst)->next->str, lst, mini))
			return ;
		node->infile = ut_strdup((*lst)->next->str);
		if (!node->infile)
			ut_clean_parsing_n_quit(mini, lst, errno);
		node->in_file = 1;
		clean_lst_mode(dest, temp, lst, 1);
		return ;
	};
	temp = *lst;
	while (!ut_strcmp(temp->next->str, dest->str))
		temp = temp->next;
	if (temp->next->next == NULL)
		printf("shellnado : syntax error near unexpected token '\\n'");
	if (check_compliance_redir(temp->next->next->str, lst, mini))
			return ;
	node->infile = ut_strdup(temp->next->next->str);
	if (!node->infile)
		ut_clean_parsing_n_quit(mini, lst, errno);
	node->in_file = 1;
	clean_lst_mode(dest, temp, lst, 2);
}

/*Handle out redir*/

void	out_redir(t_tok **lst, t_tok *dest, t_cati *node, t_cati **mini)
{
	t_tok	*temp;

	temp = 0;
	if (ut_strcmp((*lst)->str, dest->str))
	{
		if ((*lst)->next && check_compliance_redir((*lst)->next->str, lst, mini))
			return ;
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
	printf("temp->next = %p temp->next->next = %p", temp->next, temp->next->next);
	if (temp->next->next == NULL)
		printf("shellnado : syntax error near unexpected token '\\n'");
	if (temp->next->next && check_compliance_redir(temp->next->next->str, lst, mini))
			return ;
	node->outfile = ut_strdup(temp->next->next->str);
	if (!node->outfile)
		ut_clean_parsing_n_quit(mini, lst, errno);
	node->out_trunc = 1;
	clean_lst_mode(dest, temp, lst, 2);
}

/*Handle out append redir*/

void	append_redir(t_tok **lst, t_tok *dest, t_cati *node, t_cati **mini)
{
	t_tok	*temp;

	temp = 0;
	if (ut_strcmp((*lst)->str, dest->str))
	{
		if (check_compliance_redir((*lst)->next->str, lst, mini))
			return ;

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
	if (temp->next->next == NULL)
		printf("shellnado : syntax error near unexpected token '\\n'");
	if (check_compliance_redir(temp->next->next->str, lst, mini))
			return ;		
	node->outfile = ut_strdup(temp->next->next->str);
	if (!node->outfile)
		ut_clean_parsing_n_quit(mini, lst, errno);
	node->out_append = 1;
	clean_lst_mode(dest, temp, lst, 2);
}
