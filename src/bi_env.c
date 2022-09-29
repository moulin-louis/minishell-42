/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:15:43 by bschoeff          #+#    #+#             */
/*   Updated: 2022/09/27 15:09:21 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_env(char **envp)
{
	int	i;

	if (!envp || !*envp)
		return (1);
	i = -1;
	while (envp[++i])
		printf("%s\n", envp[i]);
	return (0);
}