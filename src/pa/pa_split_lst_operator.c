/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_split_lst_operator.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:26:13 by loumouli          #+#    #+#             */
/*   Updated: 2022/10/24 14:08:06 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

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

static int	split_node(t_tok *lst, t_cati **mini)
{
	int		i;
	t_tok	*temp;
	char	**result;
	t_tok	*temp2;
	t_tok	*temp3;

	result = extract_sep(lst->next->str);
	if (!result)
		return (full_exit(mini, errno), 0);
	i = -1;
	temp = NULL;
	while (result[++i])
		tok_addback(&temp, tok_new(result[i], mini));
	temp2 = lst->next;
	temp3 = lst->next->next;
	lst->next = temp;
	while (temp->next)
		temp = temp->next;
	temp->next = temp3;
	tok_delone(temp2);
	free(result[i]);
	free(result);
	return (i);
}

void	split_lst_operator(t_tok *lst, t_cati **mini)
{
	t_tok	*temp;
	int		len;

	temp = lst;
	while (temp)
	{
		if (temp->next && is_there_a_sep(temp->next->str))
		{
			len = split_node(temp, mini);
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
