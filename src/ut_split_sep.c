/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_split_sep.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:53:30 by loumouli          #+#    #+#             */
/*   Updated: 2022/10/11 12:05:55 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

static	int	ft_sep(char c, char *sep)
{
	int	i;

	i = -1;
	while (sep[++i])
	{
		if (c == sep[i])
			return (1);
	}
	return (0);
}

int	ut_word_len_sep(char *str, char *sep)
{
	int	i;

	i = 0;
	while (str[i] && ft_sep(str[i], sep))
		i++;
	return (i);
}

static int	word_count(char *str, char *sep)
{
	int	i;
	int	count;

	count = 0;
	if (!str || !*str)
		return (count);
	i = 0;
	while (str[i])
	{
		while (str[i] != '\0' && ft_sep(str[i], sep))
			i++;
		if (str[i] && ft_sep(str[i], sep))
		{
			count++;
			while (str[i] && ft_sep(str[i], sep))
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

char	**ut_split_sep(char *str, char *sep)
{
	char	**arr;
	int		words;
	int		i;
	int		len;

	words = word_count(str, sep);
	arr = malloc(sizeof(char *) * (words + 1));
	if (!arr)
		return (perror("Split malloc"), arr);
	arr[words] = 0;
	i = -1;
	while (++i < words)
	{
		if (*str)
			while (ft_sep(*str, sep))
				str++;
		len = ut_word_len_sep(str, sep);
		arr[i] = do_the_split(str, len);
		if (!arr[i])
			return (clean_split(arr), NULL);
		str += len;
	}
	return (arr);
}
