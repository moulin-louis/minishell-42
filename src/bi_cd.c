/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:19:57 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/04 20:35:46 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>

static void	change_pwd(t_cati **mini, char *str)
{
	t_cati	*tmp;

	tmp = *mini;
	(void)str;
	while (tmp)
	{
		tmp = tmp->next;
	}
}

int	bi_cd(t_cati **mini, char *str)
{
	if (!((*mini)->cmd = ut_split(str)))
		return (perror("cd split malloc"), 1);
	if (!(*mini)->cmd[1] || chdir((*mini)->cmd[1]) == -1)
		return (perror("cd"), 1);
	clean_split((*mini)->cmd);
	change_pwd(mini, ut_strjoin("PWD=", (*mini)->cmd[1]));
	return (0);
}
