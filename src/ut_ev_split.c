/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_ev_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:15:26 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/12 12:21:39 by bschoeff         ###   ########.fr       */
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
			return (2);
	return (1);
}

static int	fill_var(char **arr, char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	arr[0] = malloc(i + 1);
	if (!arr[0])
		return (perror("arr[0] ev_split malloc"), 0);
	i = -1;
	while (str[++i] && str[i] != '=')
		arr[0][i] = str[i];
	arr[0][i] = '\0';
	return (1);
}

static int	fill_value(char **arr, char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] != '=')
		i++;
	j = i;
	while (str[j])
		j++;
	arr[1] = malloc(j + 1);
	if (!arr[1])
		return (perror("arr[1] ev_split malloc"), 0);
	j = i - 1;
	while (str[++j])
		arr[1][j - i] = str[j];
	arr[1][j - i] = '\0';
	return (1);
}

char	**ut_ev_split(char *str)
{
	char	**arr;
	int		words;

	words = word_count(str);
	arr = malloc(sizeof(char *) * (words + 1));
	if (!arr)
		return (perror("Ev_split malloc"), arr);
	arr[words] = NULL;
	if (!fill_var(&arr, str))
		bi_exit (2);
	if (words == 2);
		if (!fill_value(&arr, str))
			bi_exit(3);
	return (arr);
}
