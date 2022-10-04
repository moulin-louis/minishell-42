/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 09:32:09 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/04 14:20:17 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	bi_export(t_cati **mini, char *str)
{
	int		i;
	int		ret;
	t_envp	*new;

	if (!((*mini)->cmd = ft_split(str)))
		return (perror("export split malloc"), 1);
	i = 0;
	ret = 0;
	while ((*mini)->cmd[++i])
	{
		new = malloc(sizeof(t_envp));
		if (!new)
		{
			printf("%s ", (*mini)->cmd[i]);
			perror("export malloc");
			ret++;
			break ;
		}
		new->next = NULL;
		new->var = ft_strcpy((*mini)->cmd[i]);
		if (!new->var)
			return (perror("Fatal error export malloc"), ret);
		env_lstaddback(&(*mini)->envp, new);
	}
	return (ret);
}
