/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_mini_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:51:29 by loumouli          #+#    #+#             */
/*   Updated: 2022/10/24 14:04:13 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

t_cati	*mini_lstlast(t_cati *mini)
{
	t_cati	*temp;

	temp = mini;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

void	ft_bzero(void *s, int n)
{
	char	*temp;

	temp = s;
	while (n)
	{
		*temp = 0;
		temp++;
		n--;
	}
}

void	mini_lstaddback(t_cati **mini, t_cati *node)
{
	t_cati	*temp;

	if (!*mini)
	{
		*mini = node;
		return ;
	}
	temp = *mini;
	while (temp->next)
		temp = temp->next;
	temp->next = node;
}

void	mini_delone(t_cati *node)
{
	if (node->cmd)
		clean_split(node->cmd);
	if (node->ev)
		clean_split(node->ev);
	if (node->path_cmd)
		free(node->path_cmd);
	if (node->infile)
		free(node->infile);
	if (node->outfile)
		free(node->outfile);
	free(node);
}

t_cati	*mini_lstnew(void)
{
	t_cati	*result;

	result = ut_calloc(1, sizeof(t_cati));
	if (!result)
		return (perror("Malloc :"), full_exit(&result, errno), NULL);
	ft_bzero(result, sizeof(t_cati));
	return (result);
}
