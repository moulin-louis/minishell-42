/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:15:26 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/12 09:20:01 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

static int	word_count(char *str, char c)
{
	int	i;
	int	count;

	count = 0;
	if (!str || !*str)
		return (count);
	i = 0;
	while (str[i])
	{
		while (str[i] != '\0' && str[i] == c)
			i++;
		if (str[i] && str[i] != c)
		{
			count++;
			while (str[i] && str[i] != c)
				i++;
		}
	}
	return (count);
}

static char	*do_the_split(char *s2, int len)
{
	int		i;
	char	*s1;

	s1 = malloc(len + 1);
	if (!s1)
		return (NULL);
	i = 0;
	while (i < len)
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}

char	**ut_split(char *str, char c)
{
	char	**arr;
	int		words;
	int		i;
	int		len;

	words = word_count(str, c);
	arr = malloc(sizeof(char *) * (words + 1));
	if (!arr)
		return (perror("Split malloc"), arr);
	arr[words] = 0;
	i = -1;
	while (++i < words)
	{
		if (*str)
			while (*str == c)
				str++;
		len = ut_word_len(str, c);
		arr[i] = do_the_split(str, len);
		if (!arr[i])
			return (clean_split(arr), NULL);
		str += len;
	}
	return (arr);
}
