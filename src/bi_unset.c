/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:48:15 by bschoeff          #+#    #+#             */
/*   Updated: 2022/09/27 17:10:51 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	search_path(char *s1, char *s2)
{
	int	i;

	i = -1;
	while (++i < 5)
		if (s1[i] != s2[i])
			return (0);
	return (1);
}

int	bi_unset(char **envp)
{
	int	i;

	if (!envp || !*envp)
		return (1);
	i = -1;
	while (envp[++i])
		if (search_path(envp[i], "PATH="))
			envp[i] = "\n";
	printf("PATH: %s\n", envp[i]);
	return (0);
}
