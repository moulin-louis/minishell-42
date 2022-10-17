/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_split_sep.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:53:30 by loumouli          #+#    #+#             */
/*   Updated: 2022/10/12 13:21:54 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

static int	is_op(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

static int	find_len(char *str)
{
	int	result;

	result = 0;
	if (is_op(str[result]))
	{
		while (str[result] && is_op(str[result]))
			result++;
		return (result);
	}
	else if (!is_op(str[result]))
	{
		while (str[result] && !is_op(str[result]))
			result++;
		return (result);
	}
	return (0);
}

static int	count_token(char *str)
{
	int	i;
	int	result;

	result = 0;
	i = 0;
	while (str[i])
	{
		if (!is_op(str[i]))
		{
			result++;
			while (str[i] && !is_op(str[i]))
				i++;
		}
		if (is_op(str[i]))
		{
			result++;
			while (str[i] && is_op(str[i]))
				i++;
		}
	}
	return (result);
}

static char	*split_this_op(char *str, int len)
{
	int		i;
	char	*result;

	result = malloc(len + 1);
	if (!result)
		return (NULL);
	result[len] = '\0';
	i = -1;
	while (++i < len)
		result[i] = str[i];
	return (result);
}

char	**extract_sep(char *str)
{
	char	**result;
	int		words;
	int		len;
	int		i;

	i = 0;
	len = 0;
	words = count_token(str);
	result = malloc(sizeof(char *) * (words + 1));
	if (!result)
		return (NULL);
	result[words] = 0;
	while (i < words)
	{
		len = find_len(str);
		result[i] = split_this_op(str, len);
		if (!result[i])
			return (clean_split(result), NULL);
		i++;
		str += len;
	}
	(void)i;
	(void) len;
	return (result);
}
