/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_clean_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:54:12 by loumouli          #+#    #+#             */
/*   Updated: 2022/12/05 17:07:59 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

void	trigger_cleaning(t_tok *node, t_cati **mini, t_tok **lst)
{
	char	*temp;
	int		i;

	i = 0;
	temp = malloc(ft_strlen(node->str) - 1);
	if (!temp)
		ut_clean_parsing_n_quit(mini, lst, errno);
	while (++i < ft_strlen(node->str) - 1)
		temp[i - 1] = node->str[i];
	temp[i - 1] = '\0';
	free(node->str);
	node->str = temp;
}

void	clean_quote(t_tok **lst, t_cati **mini)
{
	t_tok	*temp;

	temp = *lst;
	while (temp)
	{
		if (temp->str[0] == '\'' || temp->str[0] == '\"')
			trigger_cleaning(temp, mini, lst);
		temp = temp->next;
	}
}
