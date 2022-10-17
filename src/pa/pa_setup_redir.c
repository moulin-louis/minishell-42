/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_setup_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:42:25 by loumouli          #+#    #+#             */
/*   Updated: 2022/10/17 16:09:39 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	in_redir(t_tok **lst, t_tok *dest, t_cati *mini)
{
	t_tok	*temp;

	if (ut_strcmp((*lst)->str, dest->str))
	{
		mini->path_file = ut_strdup((*lst)->next->str);
		if (!mini->path_file)
			return ;
		mini->in_file = 1;
		temp = (*lst)->next;
		tok_delone((*lst));
		(*lst) = temp;
		temp = (*lst)->next;
		tok_delone((*lst));
		(*lst) = temp;
		return ;
	}
	temp = *lst;
	while (ut_strcmp(temp->next->str, dest->str))
		temp = temp->next;
	mini->path_file = ut_strdup(temp->next->next->str);
	if (!mini->path_file)
		return ;
	mini->in_file = 1;
	dest = temp->next;
	temp->next = temp->next->next;
	tok_delone(dest);
	dest = temp->next;
	temp->next = temp->next->next;
	tok_delone(dest);
}
