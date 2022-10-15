/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:15:26 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/15 14:46:51 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

static int	word_count(char *str)
{
	int	i;
	int	count;

	count = 0;
	if (!str || !*str)
		return (count);
	i = 0;
	while (str[i])
	{
		while (str[i] != '\0' && str[i] == ' ')
			i++;
		if (str[i] && str[i] != ' ')
		{
			count++;
			while (str[i] && str[i] != ' ')
				i++;
		}
	}
	return (count);
}

static char	*do_the_split(char *s2, int len)
{
	int		i;
	char	*s1;

	s1 = ut_calloc(len + 1, 1);
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

char	**ut_split(char *str)
{
	char	**arr;
	int		words;
	int		i;
	int		len;

	words = word_count(str);
	arr = ut_calloc(words + 1, sizeof(char *));
	if (!arr)
		return (perror("Split malloc"), arr);
	arr[words] = 0;
	i = -1;
	while (++i < words)
	{
		if (*str)
			while (*str == ' ')
				str++;
		len = ut_word_len(str);
		arr[i] = do_the_split(str, len);
		if (!arr[i])
			return (clean_split(arr), NULL);
		str += len;
	}
	return (arr);
}
