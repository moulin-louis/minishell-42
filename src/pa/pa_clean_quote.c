/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_clean_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:54:12 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/08 15:57:20 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <stdlib.h>

int	delete_node(t_tok *node, t_tok **lst, t_cati **mini)
{
	t_tok	*temp;

	(void)lst;
	(void)mini;
	if (node->str == (*lst)->str)
	{
		temp = (*lst)->next;
		tok_delone(*lst);
		*lst = temp;
		return (1);
	}
	temp = *lst;
	while (temp->next)
	{
		if (ut_strcmp(temp->next->str, node->str))
			break ;
		temp = temp->next;
	}
	temp->next = node->next;
	tok_delone(node);
	return (1);
}

/*Clean quote adn double quote*/

int	trigger_cleaning(t_tok *node, t_cati **mini, t_tok **lst)
{
	char	*temp;
	int		i;

	if (node->str[0] == '\'' && node->str[1] == '\'')
		return (delete_node(node, lst, mini));
	if (node->str[0] == '\"' && node->str[1] == '\"')
		return (delete_node(node, lst, mini));
	i = 0;
	temp = malloc(ft_strlen(node->str) - 1);
	if (!temp)
		ut_clean_parsing_n_quit(mini, lst, errno);
	while (++i < ft_strlen(node->str) - 1)
		temp[i - 1] = node->str[i];
	temp[i - 1] = '\0';
	free(node->str);
	node->str = temp;
	return (1);
}

/*Search for quote in token after expand*/

void	clean_quote(t_tok **lst, t_cati **mini)
{
	t_tok	*temp;

	temp = *lst;
	while (temp)
	{
		if (temp->str[0] == '\'' || temp->str[0] == '\"')
		{
			if (trigger_cleaning(temp, mini, lst) == 1)
			{
				temp = *lst;
				continue ;
			}
		}
		temp = temp->next;
	}
}
