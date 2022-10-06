/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:12:30 by loumouli          #+#    #+#             */
/*   Updated: 2022/10/06 15:18:30 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
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
		while (str[*i] && str[*i] != 39)
			(*i)++;
	}
	(*i)++;
}

char	*ft_return_token(char *str, int *i)
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

int	find_nbr_token(char *str, t_cati **lst)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			result++;
			ft_return_token(str, &i);
		}
		else if (str[i] != ' ' && str[i] != 34 && str[i] != 39)
		{
			result ++;
			mini_lstaddback(lst, mini_lstnew(ft_return_str(str, &i)));
		}
		else
			i++;
	}
	return (result);
}

t_cati	*tokenize_string(char *str)
{
	int		nbr_token;
	t_cati	*result;

	result = NULL;
	nbr_token = find_nbr_token(str, &result);
	return (result);
}

void	parsing(char *input)
{
	t_cati	*mini;

	mini = tokenize_string(input);
	t_cati *temp = mini;
	while (temp)
	{
		printf("%s\n", temp->path_cmd);
		temp = temp->next;
	}
	(void)mini;
}