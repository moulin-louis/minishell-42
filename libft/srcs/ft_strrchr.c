/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:34:43 by loumouli          #+#    #+#             */
/*   Updated: 2022/05/09 17:52:29 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	x;

	x = 0;
	if (c > 0)
		c = (char)c;
	while (*s)
	{
		s++;
		x++;
	}
	while (x >= 0)
	{
		if (*s == c)
			return ((char *) s);
		s--;
		x--;
	}
	return (0);
}
