/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_mini_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:51:29 by loumouli          #+#    #+#             */
/*   Updated: 2022/10/15 14:46:14 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

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

void	mini_delone(t_cati	*node)
{
	if (node->cmd)
		clean_split(node->cmd);
	if (node->path_cmd)
		free(node->path_cmd);
	if (node->path_file)
		free(node->path_file);
	free(node);
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

t_cati	*mini_lstnew(void)
{
	t_cati	*result;

	result = ut_calloc(1, sizeof(t_cati));
	if (!result)
		return (NULL);
	ft_bzero(result, sizeof(t_cati));
	return (result);
}
