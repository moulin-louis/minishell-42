/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_strstuff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 12:32:42 by loumouli          #+#    #+#             */
/*   Updated: 2022/10/15 14:47:23 by bschoeff         ###   ########.fr       */
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

char	*ut_strdup(char *str)
{
	char	*result;
	int		len;
	int		i;

	len = 0;
	i = -1;
	result = NULL;
	len = ft_strlen(str);
	result = ut_calloc(len + 1, 1);
	if (!result)
		return (NULL);
	result[len] = 0;
	while (str[++i])
		result[i] = str[i];
	return (result);
}

int	ft_strncmp(const char *s1, const char *s2, int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] == s2[i]) && s1[i] != 0 && s2[i] != 0 && i < n -1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
