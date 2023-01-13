/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:42:31 by bschoeff          #+#    #+#             */
/*   Updated: 2023/01/13 12:20:14 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

static void	already_exists(t_cati **mini, char *str)
{
	t_envp	*tmp;

	tmp = (*mini)->envp;
	while (tmp)
	{
		if (ut_strcmp(tmp->var[0], str))
		{
			env_lstdelone(&(*mini)->envp, tmp);
			break ;
		}
		tmp = tmp->next;
	}
}

int	bi_unset(t_cati **mini, t_cati *node)
{
	int		i;

	g_status = 0;
	if (!node->cmd[1])
		return (0);
	if (ft_strlen(node->cmd[1]) >= 2)
	{
		if (node->cmd[1][0] == '-')
		{
			ut_putstr_fd("bash: unset: ", 2);
			write(2, &node->cmd[1][0], 2);
			ut_putstr_fd(": ", 2);
			ut_putstr_fd("invalid option\n", 2);
			g_status = 2;
			return (2);
		}
	}
	i = 0;
	while (node->cmd[++i])
		already_exists(mini, node->cmd[i]);
	return (g_status);
}
