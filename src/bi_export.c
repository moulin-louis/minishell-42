/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 09:32:09 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/04 11:32:28 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	bi_export(t_cati **mini)
{
	int		i;
	t_envp	*new;

	i = 0;
	while ((*mini)->cmd[++i])
	{
		new = malloc(sizeof(t_envp));
		if (!new)
			return (perror("Export malloc"), 1);
		new->next = NULL;
		new->var = ft_strcpy((*mini)->cmd[i]);
		env_lstaddback(&(*mini)->envp, new);
	}
	return (0);
}
