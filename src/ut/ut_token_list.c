/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_token_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:04:37 by loumouli          #+#    #+#             */
/*   Updated: 2022/10/26 16:40:34 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

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

t_tok	*tok_new(char *str, t_cati **mini, t_tok **lst)
{
	t_tok	*result;

	if (!str)
		ut_clean_parsing_n_quit(mini, lst, 1);
	result = ut_calloc(1, sizeof(t_tok));
	if (!result)
		return (perror("Malloc :"), full_exit(mini, errno), NULL);
	result->str = str;
	result->next = NULL;
	return (result);
}
