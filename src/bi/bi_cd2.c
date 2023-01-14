/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:23:48 by foster            #+#    #+#             */
/*   Updated: 2023/01/14 16:32:43 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <string.h>
#include <errno.h>

int	cd_home(t_cati **mini)
{
	t_envp	*tmp;

	tmp = (*mini)->envp;
	while (tmp)
	{
		if (ut_strcmp("HOME", tmp->var[0]) && tmp->var[1][0])
		{
			if (chdir(tmp->var[1]) == -1)
			{
				ut_putstr_fd("bash: cd: ", 2);
				ut_putstr_fd(tmp->var[1], 2);
				ut_putstr_fd(": ", 2);
				ut_putstr_fd(strerror(errno), 2);
				ut_putstr_fd("\n", 2);
				g_var.g_status = 1;
				return (-1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}
