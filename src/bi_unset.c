/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:42:31 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/03 14:24:05 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

int	bi_unset(t_envp **envp, char *var)
{
	t_envp	*tmp;
	int		i;
	int		len;
	int		match;

	if (!var || !*var)
		return (1);
	len = 0;
	while (var[len])
		len++;
	tmp = *envp;
	while (tmp)
	{
		i = -1;
		match = 1;
		while (++i < len)
		{
			if (tmp->var[i] != var[i])
			{
				match = 0;
				break ;
			}
		}
	}
}
