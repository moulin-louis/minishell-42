/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:15:43 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/03 13:26:28 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int	bi_env(t_envp **envp)
{
	t_envp	*tmp;
	int		i;

	tmp = *envp;
	i = -1;
	while (tmp)
	{
		printf("%s\n", tmp->var);
		tmp = tmp->next;
	}
	return (0);
}
