/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:15:43 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/08 11:31:18 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int	bi_env(t_cati **mini)
{
	t_envp	*tmp;

	tmp = (*mini)->envp;
	while (tmp)
	{
		printf("%s\n", tmp->var);
		tmp = tmp->next;
	}
	return (0);
}
