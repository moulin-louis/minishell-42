/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:29:31 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/13 12:28:56 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

/*Create a new string like s3 = s1 + s2 and return the mallocated ptr*/

char	*ut_strjoin(char *s1, char *s2)
{
	char	*str;
	int		ls1;
	int		ls2;
	int		i;

	ls1 = ft_strlen(s1);
	ls2 = ft_strlen(s2);
	str = ut_calloc(ls1 + ls2 + 1, 1);
	if (!str)
		return (ut_putstr_fd("Malloc error in strjoin\n", 2), NULL);
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
