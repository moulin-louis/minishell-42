/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_mini_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:51:29 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/13 12:28:14 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <errno.h>

/*All sort of utilts for t_cati linked list*/

/*return a ptr to the last node of the t_cati linked list*/

t_cati	*mini_lstlast(t_cati *mini)
{
	t_cati	*temp;

	temp = mini;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

/*Add the t_cati node to the back of the t_cati linked list*/

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

/*Create a new t_cati node and return its ptr, quit minishell if fail*/

t_cati	*mini_lstnew(void)
{
	t_cati	*result;

	result = ut_calloc(1, sizeof(t_cati));
	if (!result)
		return (NULL);
	return (result);
}
