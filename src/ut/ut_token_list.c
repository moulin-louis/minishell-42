/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_token_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:04:37 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/13 12:29:09 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <errno.h>

/*All sort of utilts for t_tok linked list*/

/*Delete t_tok node*/

void	tok_delone(t_tok *node)
{
	free(node->str);
	free(node);
}

/*Clean all the t_tok linked list from the ptr*/

void	clean_tok(t_tok **lst)
{
	t_tok	*temp;

	if (!lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		if ((*lst)->str)
			free((*lst)->str);
		free((*lst));
		*lst = temp;
	}
}

/*Add t_tok node to the back of t_tok linked list*/

void	tok_addback(t_tok **lst, t_tok *node)
{
	t_tok	*temp;

	if (!(*lst))
	{
		*lst = node;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = node;
}

/*Create a new t_tok node, crash minishell if malloc failed*/

t_tok	*tok_new(char *str)
{
	t_tok	*result;

	if (!str)
		return (NULL);
	result = ut_calloc(1, sizeof(t_tok));
	if (!result)
		return (NULL);
	result->str = str;
	result->next = NULL;
	return (result);
}
