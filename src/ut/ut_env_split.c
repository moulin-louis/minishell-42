/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_env_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 12:26:44 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/13 12:28:05 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

/*Count the nbr of worf in string based on '='*/

int	word_count(char *str)
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

/*Fill the 0 of the dbl array by the name of the var*/

int	fill_var(char **arr, const char *str)
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

/*Malloc of 1 if the value is null*/

int	fill_empty_val(char **arr)
{
	arr[1] = ut_calloc(1, 1);
	if (!arr[1])
		return (0);
	return (1);
}

/*Fill the 1 of the dbl array by the value*/

int	fill_value(char **arr, char *str)
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

/*Create a double array of string based on a string
Split based on the char '='
Return NULL if fail*/

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
		return (free(arr), NULL);
	if (words == 2)
		if (!fill_empty_val(arr))
			return (free(arr[0]), free(arr), NULL);
	if (words == 3)
		if (!fill_value(arr, str))
			return (free(arr[0]), free(arr), NULL);
	return (arr);
}
