/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_mini_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:51:29 by loumouli          #+#    #+#             */
/*   Updated: 2022/10/06 14:00:58 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_bzero(void *s, size_t n)
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

t_cati	*mini_lstnew(char *str)
{
	t_cati	*result;

	result = malloc(sizeof(t_cati));
	if (!result)
		return (NULL);
	ft_bzero(result, sizeof(t_cati));
	result->path_cmd = str;
	return (result);
}
