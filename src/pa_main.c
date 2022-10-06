/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:12:30 by loumouli          #+#    #+#             */
/*   Updated: 2022/10/05 15:34:01 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	add_i(char *str, int *i)
{
	if (str[(*i) - 1] == 34)
		while (str[*i] && str[*i] != 34)
			(*i)++;
	if (str[(*i) - 1] == 39)
		while (str[*i] && str[*i] != 39)
			(*i)++;
}

int	find_nbr_token(char *str)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			i++;
			result++;
			add_i(str, &i);
			i++;
		}
		else if (str[i] != ' ' && str[i] != 34 && str[i] != 39)
		{
			result ++;
			while (str[i] && str[i] != ' ' && str[i] != 34 && str[i] != 39)
				i++;
		}
		else
			i++;
	}
	return (result);
}

char	**tokenize_string(char *str)
{
	char	**result;
	int		nbr_token;

	result = NULL;
	nbr_token = find_nbr_token(str);
	result = malloc(sizeof(char *) * (nbr_token + 1));
	if (!result)
		return (NULL);
	result[nbr_token] = NULL;
	return (result);
}

void	parsing(char *input)
{
	char	**token_str;

	token_str = tokenize_string(input);
	(void)token_str;
}
