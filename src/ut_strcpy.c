/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_strcpy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 09:01:34 by bschoeff          #+#    #+#             */
/*   Updated: 2022/09/30 09:37:09 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strcpy(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		len;

	if (!s2)
		NULL;
	len = 0;
	while (s2[len])
		len++;
	s1 = malloc(len + 1);
	if (!s1)
		return (perror("String malloc"), NULL);
	i = 0;
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
}
