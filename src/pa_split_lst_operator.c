/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_split_lst_operator.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:26:13 by loumouli          #+#    #+#             */
/*   Updated: 2022/10/11 12:03:17 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	split_node(t_tok **lst)
{
	///int		i;
	//t_tok	*temp;

	char **result = ut_split_sep((*lst)->str, "|<>");
	if (result)
		printf("[%s]\n", result[0]);
}

void	split_lst_operator(t_tok **lst)
{
	t_tok	**temp;

	temp = lst;
	while (*temp)
	{
		if (ft_is_sep((*temp)->str))
			split_node(temp);
		*temp = (*temp)->next;
	}
}
