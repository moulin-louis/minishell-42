/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:15:43 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/16 17:10:03 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int	bi_env(t_cati **mini)
{
	t_envp	*tmp;

	g_var.g_status = 0;
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
	return (g_var.g_status);
}
