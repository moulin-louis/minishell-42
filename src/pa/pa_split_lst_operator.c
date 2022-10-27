/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_split_lst_operator.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli < loumouli@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:26:13 by loumouli          #+#    #+#             */
/*   Updated: 2022/10/27 19:40:02 by loumouli         ###   ########.fr       */
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

void	fill_lst(char **result, t_tok *node, t_cati **mini, t_tok **lst)
{
	t_tok	*temp;
	t_tok	*temp2;
	int		i;

	free(node->str);
	node->str = ut_strdup(result[0]);
	if (!node->str)
	{
		clean_split(result);
		ut_clean_parsing_n_quit(mini, lst, errno);
	}
	i = 0;
	while (result[++i])
	{
		temp = tok_new(ut_strdup(result[i]), mini, lst);
		temp2 = node->next;
		node->next = temp;
		temp->next = temp2;
		node = node->next;
	}
}

static int	split_node(t_tok *node, t_cati **mini, t_tok **lst)
{
	char	**result;
	int		i;

	result = extract_sep(node->str);
	if (!result)
		ut_clean_parsing_n_quit(mini, lst, errno);
	fill_lst(result, node, mini, lst);
	i = -1;
	while (result[++i])
		;
	clean_split(result);
	return (i);
}

void	split_lst_operator(t_tok **lst, t_cati **mini)
{
	t_tok	*temp;
	int		len;

	temp = *lst;
	while (temp)
	{
		if (is_there_a_sep(temp->str))
		{
			len = split_node(temp, mini, lst);
			while (len)
			{
				temp = temp->next;
				len--;
			}
		}
		else
			temp = temp->next;
	}
}
