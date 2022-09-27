/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:38:50 by loumouli          #+#    #+#             */
/*   Updated: 2022/05/09 14:46:55 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char	*temp1;
	char	*temp2;

	temp1 = (char *)s1;
	temp2 = (char *)s2;
	if (n == 0)
		return (0);
	while (*temp1 == *temp2 && n != 1)
	{
		temp1++;
		temp2++;
		n--;
	}
	return ((unsigned char)*temp1 - (unsigned char)*temp2);
}
