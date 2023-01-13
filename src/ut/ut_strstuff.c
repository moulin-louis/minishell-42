/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_strstuff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 12:32:42 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/13 12:29:05 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

/*Some tools for string*/

/*Return the len of the string, 0 excluded*/

int	ft_strlen(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

/*Copy str string and return the new malloced ptr*/

char	*ut_strdup(char *str)
{
	char	*result;
	int		len;
	int		i;

	i = -1;
	len = ft_strlen(str);
	result = ut_calloc(len + 1, 1);
	if (!result)
		return (NULL);
	result[len] = 0;
	while (str[++i])
		result[i] = str[i];
	return (result);
}

/*Return 0 if the n first char of s1 and s2 are the same*/

int	ft_strncmp(const char *s1, const char *s2, int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] == s2[i]) && s1[i] != 0 && i < n -1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
