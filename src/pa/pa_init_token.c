/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_init_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 10:41:05 by loumouli          #+#    #+#             */
/*   Updated: 2022/10/17 18:24:09 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

static void	add_i(char *str, int *i)
{
	if (str[(*i) - 1] == 34)
	{
		while (str[*i] && str[*i] != 34)
			(*i)++;
	}
	if (str[(*i) - 1] == 39)
	{
		while (str[*i] && str[*i] != 39)
			(*i)++;
	}
	(*i)++;
}

static char	*ft_return_token(char *str, int *i)
{
	int		temp;
	int		len;
	char	*result;

	temp = *i;
	add_i(str, i);
	len = (*i) - temp;
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	result[len] = '\0';
	len = 0;
	while (temp < *i)
	{
		result[len] = str[temp];
		len++;
		temp++;
	}
	return (result);
}

static char	*ft_return_str(char *str, int *i)
{
	int		temp;
	char	*result;

	temp = *i;
	while (str[temp] && str[temp] != ' ' && str[temp] != 34 && str[temp] != 39)
		temp++;
	printf("Je malloc de %d bytes\n", (temp - *i) + 1);
	result = malloc(sizeof(char) * ((temp - *i) + 1));
	if (!result)
		return (NULL);
	result[(temp - *i)] = '\0';
	temp = 0;
	while (str[*i] && str[*i] != ' ' && str[*i] != 34 && str[*i] != 39)
	{
		result[temp] = str[*i];
		(*i)++;
		temp++;
	}
	return (result);
}

t_tok	*init_token_list(char *str)
{
	int		i;
	t_tok	*result;

	i = 0;
	result = NULL;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			tok_addback(&result, tok_new(ft_return_token(str, &i)));
		else if (str[i] != ' ' && str[i] != 34 && str[i] != 39)
			tok_addback(&result, tok_new(ft_return_str(str, &i)));
		else
			i++;
	}
	return (result);
}
