/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_split_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 19:32:51 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/13 12:28:30 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

/*WARNING : Its suposed to be a split based on a given char, but the fn word_len
is hard code to work with ':' char */

/*WARNING : BAD FN
count the len to the next ':' occurence*/

static int	word_len(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ':')
		i++;
	return (i);
}

/*Count the nbr of word based on char as a separator*/

static int	word_count(const char *str, char c)
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

/*Create the string based on s2 string and the given len*/

static char	*do_the_split(const char *s2, int len)
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

/*Split a string into a double array of string based on a sep, return the
 malloced doublle array of string*/

char	**ut_split_char(const char *str, char c)
{
	char	**arr;
	int		words;
	int		i;
	int		len;

	words = word_count(str, c);
	arr = ut_calloc(words + 1, sizeof(char *));
	if (!arr)
		return (perror("Split malloc"), arr);
	arr[words] = 0;
	i = -1;
	while (++i < words)
	{
		if (*str)
			while (*str == c)
				str++;
		len = word_len(str);
		arr[i] = do_the_split(str, len);
		if (!arr[i])
			return (clean_split(arr), NULL);
		str += len;
	}
	return (arr);
}
