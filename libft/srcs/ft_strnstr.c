/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:08:39 by loumouli          #+#    #+#             */
/*   Updated: 2022/05/10 11:12:57 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int	count;
	int	start;
	int	end;

	if (little[0] == '\0')
		return ((char *) big);
	count = 0;
	while (big[count] && len > 0)
	{
		if (len < ft_strlen(little))
			return (NULL);
		start = 0;
		end = count;
		while (big[end] == little[start] && big[end] && little[start])
		{
			start++;
			end++;
		}
		if (little[start] == '\0')
			return ((char *) big + count);
		len--;
		count++;
	}
	return (NULL);
}
