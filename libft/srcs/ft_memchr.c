/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:35:10 by loumouli          #+#    #+#             */
/*   Updated: 2022/05/09 17:41:44 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	int		i;
	char	*temp;

	if (c > 0)
		c = (char)c;
	if (n == 0)
		return (NULL);
	i = 0;
	temp = (char *)s;
	while (i < (int)n)
	{
		if (*temp == c)
			return ((void *)temp);
		i++;
		temp++;
	}
	return (0);
}
