/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_in_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:01:06 by loumouli          #+#    #+#             */
/*   Updated: 2022/10/12 16:20:57 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static int	is_infile(char *str)
{
	if (str[0] == '<' && !str[1])
		return (1);
	return (0);
}

static void	token_is_first(t_tok**lst, t_cati *mini)
{
	t_tok	*temp;

	mini->path_file = ut_strdup((*lst)->next->str);
	mini->in_file = 1;
	temp = *lst;
	*lst = (*lst)->next;
	free(temp->str);
	free(temp);
	temp = *lst;
	*lst = (*lst)->next;
	free(temp->str);
	free(temp);
}

static void	token_is_second(t_tok **lst, t_cati *mini)
{
	t_tok	*temp;
	t_tok	*temp2;

	temp = *lst;
	while (temp && !ut_strcmp(temp->next->str, "<"))
		temp = temp->next;
	mini->path_file = ut_strdup(temp->next->next->str);
	if (!mini->path_file)
		return ;
	mini->in_file = 1;
	temp2 = temp->next;
	temp->next = temp->next->next;
	free(temp2->str);
	free(temp2);
	temp2 = temp->next;
	temp->next = temp->next->next;
	free(temp2->str);
	free(temp2);
}

void	handle_in_redirection(t_tok **lst, t_cati *mini)
{
	if (is_infile((*lst)->str))
		token_is_first(lst, mini);
	else if (is_infile((*lst)->next->str))
		token_is_second(lst, mini);
}
