/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:15:26 by bschoeff          #+#    #+#             */
/*   Updated: 2022/09/30 13:23:30 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	split_da_shit(char **arr, char *str)
{
	int	len;
	int	i;

	return (1);
}

static int	word_count(char *str)
{
	int	i;
	int	count;

	count = 0;
	if (!str || !*str)
		return (count);
	i = -1;
	while (str[++i])
	{
		if (str[i] != ' ')
		{
			count++;
			while (str[i] != ' ')
				i++;
		}
	}
	return (count);
}

char	**ft_split(char *str)
{
	char	**arr;
	int		words;

	arr = NULL;
	words = word_count(str);
	printf("words in ft_split: %i\n", words);
	arr = malloc(sizeof(char *) * (words + 1));
	if (!arr)
		return (perror("Split malloc"), arr);
	arr[words] = 0;
	if (split_da_shit(arr, str))
		return (arr);
	return (NULL);
}
