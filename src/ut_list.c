/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 09:55:52 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/03 12:12:03 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

void	lstaddback(t_envp **envp, t_envp *new)
{
	t_envp	*tmp;

	if (!*envp)
	{
		*envp = new;
		return ;
	}
	tmp = *envp;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	lstclear(t_envp **envp)
{
	t_envp	*tmp;

	while (*envp)
	{
		tmp = *envp;
		*envp = (*envp)->next;
		if (tmp->var)
			free(tmp->var);
		free(tmp);
	}
}
