/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_parse_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:53:46 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/19 12:03:50 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**exe_parse_env(t_cati **mini)
{
	t_envp	*tmp;
	int		size;
	char	**arr;

	tmp = (*mini)->envp;
	size = env_lstsize((*mini)->envp);
	arr = ut_calloc(size + 1, sizeof(char *));
	if (!arr)
	{
		(*mini)->
	}
}
