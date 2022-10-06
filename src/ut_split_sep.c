/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_split_sep.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 12:49:56 by loumouli          #+#    #+#             */
/*   Updated: 2022/10/05 11:56:32 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

static	int	ft_is_sep(char c, char *sep)
{
	int	i;

	i = 0;
	while (sep[i])
	{
		if (sep[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	find_len(char *str, char *sep)
{
	int	i;

	i = 0;
	while (str[i] && !ft_is_sep(str[i], sep))
		i++;
	return (i);
}

static	int	ft_word_count(char *str, char *sep)
{
	int	i;
	int	result;

	result = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && ft_is_sep(str[i], sep))
			i++;
		while (str[i] && !ft_is_sep(str[i], sep))
		{
			result ++;
			while (str[i] && !ft_is_sep(str[i], sep))
				i++;
		}
	}
	return (result);
}

static	char	*do_the_split(char *str, int len)
{
	char	*result;
	int		i;

	result = malloc(len + 1);
	if (!result)
		return (perror("Split malloc"), NULL);
	i = 0;
	while (i < len)
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	**ft_split_sep(char *str, char *sep)
{
	char	**result;
	int		nbr_word;
	int		i;
	int		len;

	nbr_word = ft_word_count(str, sep);
	printf("there is %d word\n", nbr_word);
	result = malloc(sizeof(char *) * (nbr_word + 1));
	if (!result)
		return (perror("Split malloc"), NULL);
	result[nbr_word] = NULL;
	i = -1;
	while (++i < nbr_word)
	{
		if (*str)
			while (ft_is_sep(*str, sep))
				str++;
		len = find_len(str, sep);
		result[i] = do_the_split(str, len);
		if (!result[i])
			return (clean_split(result), NULL);
		str += len;
	}
	return (result);
}
