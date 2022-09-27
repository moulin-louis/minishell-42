/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 10:36:08 by loumouli          #+#    #+#             */
/*   Updated: 2022/05/11 12:08:18 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*result;

	if (nmemb != 0 && (nmemb * size) / nmemb != size)
		return (NULL);
	result = malloc (nmemb * size);
	if (!result)
		return (NULL);
	ft_bzero(result, (int)(nmemb * size));
	return (result);
}
