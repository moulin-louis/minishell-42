/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:09:43 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/26 10:52:24 by bschoeff         ###   ########.fr       */
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
	free(s1);
	return (str);
}
