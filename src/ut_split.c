/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:15:26 by bschoeff          #+#    #+#             */
/*   Updated: 2022/09/30 10:46:24 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	word_len(char *str, int j)
{
	int	len;

	len = 0;
	while (str[j] && str[j] != ' ')
	{
		len++;
		j++;
	}
	return (len);
}

static void	clean_split(char **array, int i)
{
	while (i >= 0)
	{
		free(array[i]);
		i--;
	}
	free(array);
}

static int	do_the_split(char **array, char *str, int words)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	while (++i < words)
	{
		j = -1;
		while (str[++j])
		{
			while (str[j] && str[j] == ' ')
				j++;
			len = word_len(str, j);
			array[i] = malloc(len + 1);
			if (!array[i])
				return (clean_split(array, i), 0);
			array[i][len] = '\0';
			len = 0;
			while (str[j] && str[j] != ' ')
			{
				array[i][len] = str[j];
				len++;
				j++;
			}
			array[i][len] = '\0';
		}
	}
	printf("leaving do_the_split\n");
	return (1);
}

static int word_count(char *str, char c)
{
	int	i;
	int	count;

	count = 0;
	if (!*str)
		return (count);
	i = -1;
	while (str[++i])
	{
		if (str[i] != c)
		{
			count++;
			while (str[i + 1] && str[i] != c)
				i++;
		}
	}
	return (count);
}

char	**ft_split(char *str)
{
	char	**array;
	int		words;

	array = NULL;
	if (!str)
		return (NULL);
	words = word_count(str, ' ');
	if (!words)
		return (NULL);
	array = malloc(sizeof(char *) * (words + 1));
	if (!array)
		return (NULL);
	array[words] = 0;
	printf("going into do_the_split in ft_split\n");
	if (do_the_split(array, str, words))
		return (array);
	return (NULL);
}
