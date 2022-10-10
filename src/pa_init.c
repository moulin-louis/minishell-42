/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 10:41:05 by loumouli          #+#    #+#             */
/*   Updated: 2022/10/10 11:13:39 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	add_i(char *str, int *i)
{
	if (str[(*i) - 1] == 34)
	{
		while (str[*i] && str[*i] != 34)
			(*i)++;
	}
	if (str[(*i) - 1] == 39)
	{
		(*i)++;
		while (str[*i] && str[*i] != 39)
			(*i)++;
	}
}

char	*ft_return_token(char *str, int *i)
{
	int		temp;
	int		len;
	char	*result;

	(*i)++;
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
	(*i)++;
	return (result);
}

char	*ft_return_str(char *str, int *i)
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

void	find_nbr_token(char *str, t_cati **lst)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			mini_lstaddback(lst, mini_lstnew(ft_return_token(str, &i)));
		else if (str[i] != ' ' && str[i] != 34 && str[i] != 39)
			mini_lstaddback(lst, mini_lstnew(ft_return_str(str, &i)));
		else
			i++;
	}
}

t_cati	*tokenize_string(char *str)
{
	t_cati	*result;

	result = NULL;
	find_nbr_token(str, &result);
	return (result);
}
