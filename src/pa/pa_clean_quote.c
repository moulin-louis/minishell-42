/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_clean_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:54:12 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/10 11:07:40 by loumouli         ###   ########.fr       */
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

int	trigger_cleaning(t_tok *node, t_cati **mini, t_tok **lst)
{
	char	*temp;
	int		i;

	if (node->str[0] == '\'' && node->str[1] == '\'')
		return (create_empty_node(node, lst, mini), 1);
	if (node->str[0] == '\"' && node->str[1] == '\"')
		return (create_empty_node(node, lst, mini), 1);
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
