/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:09:19 by loumouli          #+#    #+#             */
/*   Updated: 2022/09/29 15:48:13 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_cati	*ft_lstnew(void)
{
	t_cati	*result;

	result = malloc(sizeof(t_cati));
	if (!result)
		return (NULL);
	ft_bzero(result, sizeof(t_cati));
	return (result);
}

t_cati	*ft_lstlast(t_cati *mini)
{
	t_cati	*temp;

	temp = mini;
	while (temp)
	{
		if (temp->next == NULL)
			return (temp);
		temp = temp->next;
	}
	return (temp);
}

void	ft_lst_add_back(t_cati **mini, t_cati *node)
{
	t_cati	*temp;

	temp = ft_lstlast(*mini);
	temp->next = node;
}

void	ft_lstclear(t_cati **mini)
{
	t_cati	*temp;

	while (*mini)
	{
		temp = (*mini)->next;
		free(*mini);
		*mini = temp;
	}
}
