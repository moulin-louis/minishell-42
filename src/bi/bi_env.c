/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:15:43 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/28 08:25:57 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int	bi_env(t_cati **mini)
{
	t_envp	*tmp;

	g_status = 0;
	tmp = (*mini)->envp;
	while (tmp)
	{
		if (tmp->var[1])
		{
			printf("%s", tmp->var[0]);
			printf("=");
			printf("%s\n", tmp->var[1]);
		}
		tmp = tmp->next;
	}
	return (g_status);
}
