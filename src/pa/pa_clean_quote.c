/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_clean_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:54:12 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/13 12:23:52 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <stdlib.h>

void	create_empty_node(t_tok *node, t_tok **lst, t_cati **mini)
{
	char	*temp;

	temp = malloc(1);
	if (!temp)
		ut_clean_parsing_n_quit(mini, lst, errno);
	temp[0] = '\0';
	free(node->str);
	node->str = temp;
}

void	shift_backward_string(int pos, t_tok *node)
{
	while (node->str[pos])
	{
		node->str[pos] = node->str[pos + 1];
		pos++;
	}
	node->str[pos] = '\0';
}

int	trigger_cleaning(int *pos, t_tok *node, t_cati **mini, t_tok **lst)
{
	if ((node->str[0] == '\'' && node->str[1] == '\'' && !node->str[2]))
		return ((*pos) = (*pos) + 2, create_empty_node(node, lst, mini), 1);
	if ((node->str[0] == '\"' && node->str[1] == '\"' && !node->str[2]))
		return ((*pos) = (*pos) + 2, create_empty_node(node, lst, mini), 1);
	if (node->str[*pos] == '\"')
	{
		shift_backward_string(*pos, node);
		if (node->str[*pos] == '\"')
			return (shift_backward_string(*pos, node), (*pos) = -1, 0);
		while (node->str[*pos] && node->str[*pos] != '\"')
			(*pos)++;
		shift_backward_string(*pos, node);
		(*pos)--;
	}
	else if (node->str[*pos] == '\'')
	{
		shift_backward_string(*pos, node);
		if (node->str[*pos] == '\'')
			return (shift_backward_string(*pos, node), (*pos) = -1, 0);
		while (node->str[*pos] && node->str[*pos] != '\'')
			(*pos)++;
		shift_backward_string(*pos, node);
		(*pos)--;
	}
	return (0);
}

/*Search for quote in token after expand*/

void	clean_quote(t_tok **lst, t_cati **mini)
{
	t_tok	*temp;
	int		pos;

	temp = *lst;
	while (temp)
	{
		pos = -1;
		while (temp->str && temp->str[++pos])
		{
			if (temp->str[pos] == '\'' || temp->str[pos] == '\"')
			{
				if (trigger_cleaning(&pos, temp, mini, lst) == 1)
					break ;
			}
		}
		temp = temp->next;
	}
}
