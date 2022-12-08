/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:29:31 by loumouli          #+#    #+#             */
/*   Updated: 2022/12/06 16:18:58 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

static int	len(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (i);
	while (s[i])
		i++;
	return (i);
}

char	*ut_strjoin(char *s1, char *s2)
{
	char	*str;
	int		ls1;
	int		ls2;
	int		i;

	ls1 = len(s1);
	ls2 = len(s2);
	str = ut_calloc(ls1 + ls2 + 1, 1);
	if (!str)
		return (printf("Malloc error in strjoin\n"), NULL);
	i = -1;
	if (s1)
		while (s1[++i])
			str[i] = s1[i];
	i = -1;
	if (s2)
		while (s2[++i])
			str[i + ls1] = s2[i];
	str[i + ls1] = '\0';
	return (str);
}
