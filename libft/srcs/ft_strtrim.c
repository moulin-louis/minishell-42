/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:02:07 by loumouli          #+#    #+#             */
/*   Updated: 2022/09/04 21:29:53 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_is_set(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static	char	*ft_fill_result(char *result, int j, int i, char *s1)
{
	int	x;

	x = -1;
	while (++x <= (j - i))
		result[x] = ((char *)s1)[i + x];
	result[x] = '\0';
	return (result);
}

char	*ft_strtrim(char const*s1, char const *set)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	while (ft_is_set(((char *)s1)[i], (set)) && *s1)
		i++;
	if (!((char *)s1)[i])
	{
		result = malloc(1);
		result[0] = '\0';
		return (result);
	}
	while (s1[j + 1])
		j++;
	while (ft_is_set(((char *)s1)[j], (char *)set) && *s1)
		j--;
	if (j < 0)
		return (NULL);
	result = malloc(sizeof(char) * ((j - i) + 2));
	if (!result)
		return (NULL);
	return (ft_fill_result(result, j, i, (char *)s1));
}
