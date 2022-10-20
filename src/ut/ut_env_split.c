/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_env_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:15:26 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/20 16:47:24 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

static int	word_count(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
		{
			if (!str[i + 1])
				return (2);
			else
				return (3);
		}
	}
	return (1);
}

static int	fill_var(char **arr, char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '+' && str[i] != '=')
		i++;
	arr[0] = ut_calloc(i + 1, 1);
	if (!arr[0])
		return (perror("arr[0] ev_split malloc"), 0);
	i = -1;
	while (str[++i] && str[i] != '+' && str[i] != '=')
		arr[0][i] = str[i];
	arr[0][i] = '\0';
	return (1);
}

static int	fill_empty_val(char **arr)
{
	arr[1] = ut_calloc(1, 1);
	if (!arr[1])
		return (0);
	return (1);
}

static int	fill_value(char **arr, char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] != '=')
		i++;
	if (!str[i + 1])
	{
		arr[1] = NULL;
		return (1);
	}
	j = i;
	while (str[j])
		j++;
	arr[1] = ut_calloc(j + 1, 1);
	if (!arr[1])
		return (perror("arr[1] ev_split malloc"), 0);
	arr[1][j] = '\0';
	j = i;
	while (str[++j])
		arr[1][j - i - 1] = str[j];
	return (1);
}

char	**ut_env_split(char *str)
{
	char	**arr;
	int		words;

	words = word_count(str);
	arr = ut_calloc(words + 1, sizeof(char *));
	if (!arr)
		return (perror("Ev_split malloc"), arr);
	arr[words] = NULL;
	if (!fill_var(arr, str))
		return (arr);
	if (words == 2)
		if (!fill_empty_val(arr))
			return (arr);
	if (words == 3)
		if (!fill_value(arr, str))
			return (arr);
	return (arr);
}
