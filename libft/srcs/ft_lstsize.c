/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:33:03 by loumouli          #+#    #+#             */
/*   Updated: 2022/05/11 13:20:57 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		result;
	t_list	*lst_temp;

	lst_temp = lst;
	result = 0;
	if (!lst)
		return (0);
	if (lst_temp->next == NULL)
		return (1);
	while (lst_temp->next)
	{
		lst_temp = lst_temp->next;
		result++;
	}
	result++;
	return (result);
}
