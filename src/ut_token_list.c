/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_token_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:04:37 by loumouli          #+#    #+#             */
/*   Updated: 2022/10/10 14:41:14 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

int	tok_len(t_tok *lst)
{
	int		result;
	t_tok	*temp;

	result = 0;
	temp = lst;
	while (temp)
	{
		result++;
		temp = temp->next;
	}
	return (result);
}

void	tok_delone(t_tok *node)
{
	if (node->str)
		free(node->str);
	free(node);
}

void	clean_tok(t_tok **lst)
{
	t_tok	*temp;

	while (*lst)
	{
		temp = (*lst)->next;
		if ((*lst)->str)
			free((*lst)->str);
		free((*lst));
		*lst = temp;
	}
}

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

t_tok	*tok_new(char *str)
{
	t_tok	*result;

	result = malloc(sizeof(t_tok));
	if (!result)
		return (NULL);
	result->str = str;
	result->next = NULL;
	return (result);
}
