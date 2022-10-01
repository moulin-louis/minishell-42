/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 09:01:34 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/01 13:37:20 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

char	*ft_strcpy(char *s2)
{
	char	*str;
	int		i;
	int		len;

	if (!s2)
		return (NULL);
	len = 0;
	while (s2[len])
		len++;
	str = malloc(len + 1);
	if (!str)
		return (perror("Strcpy malloc"), NULL);
	i = 0;
	while (s2[i])
	{
		str[i] = s2[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
