/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_insert_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 21:28:09 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/07 21:36:19 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

void	trigger_join(t_tok *node, t_tok **lst, t_cati **mini)
{
	char	*result;
	t_tok	*temp;

	result = ut_strjoin(node->str, node->next->str);
	if (!result)
		ut_clean_parsing_n_quit(mini, lst, errno);
	node->str = result;
	temp = node->next;
	node->next = node->next->next;
	tok_delone(temp);
}

void	insert_token_together(t_tok **lst, t_cati **mini)
{
	t_tok	*temp;

	temp = *lst;
	while (temp)
	{
		if (temp->flag_insert == 1)
			trigger_join(temp, lst, mini);
		temp = temp->next;
	}
}
