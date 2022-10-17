/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_split_lst_operator.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:26:13 by loumouli          #+#    #+#             */
/*   Updated: 2022/10/15 13:05:11 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

static int	is_there_a_sep(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|' || str[i] == '<' || str[i] == '>')
			return (1);
		else if (str[i] == '>' && str[i + 1] == '>')
			return (1);
		else if (str[i] == '<' && str[i + 1] == '<')
			return (1);
		i++;
	}
	return (0);
}

static int	split_node(t_tok *lst)
{
	int		i;
	t_tok	*temp;
	char	**result;
	t_tok	*temp2;
	t_tok	*temp3;

	result = extract_sep(lst->next->str);
	if (!result)
		return (0);
	i = -1;
	temp = NULL;
	while (result[++i])
		tok_addback(&temp, tok_new(result[i]));
	temp2 = lst->next;
	temp3 = lst->next->next;
	lst->next = temp;
	while (temp->next)
		temp = temp->next;
	temp->next = temp3;
	free(temp2);
	free(result[i]);
	free(result);
	return (i);
}

void	split_lst_operator(t_tok *lst)
{
	t_tok	*temp;
	int		len;

	temp = lst;
	while (temp)
	{
		if (temp->next && is_there_a_sep(temp->next->str))
		{
			len = split_node(temp);
			while (len > 0)
			{
				temp = temp->next;
				len--;
			}
		}
		else
			temp = temp->next;
	}
}
