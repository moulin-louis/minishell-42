/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_init_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 10:41:05 by loumouli          #+#    #+#             */
/*   Updated: 2022/10/24 14:05:51 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

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

void	do_a_thing(t_cati **mini, t_tok **lst, int *i, char *str)
{
	t_tok	*temp;

	temp = tok_new(ft_return_token(str, i), mini);
	if (!temp)
		ut_clean_parsing_n_quit(mini, lst, errno);
	tok_addback(lst, temp);
}

t_tok	*init_token_list(char *str, t_cati **mini)
{
	int		i;
	t_tok	*result;
	t_tok	*temp;

	i = 0;
	result = NULL;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			do_a_thing(mini, &result, &i, str);
		else if (str[i] != ' ' && str[i] != 34 && str[i] != 39)
		{
			temp = tok_new(ft_return_str(str, &i), mini);
			if (!temp)
				ut_clean_parsing_n_quit(mini, &result, errno);
			tok_addback(&result, temp);
		}
		else
			i++;
	}
	return (result);
}
