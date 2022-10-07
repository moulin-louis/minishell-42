/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 09:25:48 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/07 10:11:44 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	bi_expt_expt(t_cati **mini, char *str)
{
	t_envp	*new;
	char	*ref;
	int		i;

	new = malloc(sizeof(t_envp));
	if (!new)
		return (perror("export malloc"), 0);
	new->next = NULL;
	ref = "declare -x ";
	new->var = malloc(ut_word_len(str) + 12);
	if (!new->var)
		return (perror("export malloc"), 0);
	i = -1;
	while (ref[++i])
		new->var[i] = ref[i];
	i = -1;
	while (str[++i])
		new->var[i + 11] = str[i];
	new->var[i + 11] = '\0';
	env_lstaddback(&(*mini)->expt_ev, new);
	return (1);
}

int	bi_expt_env(t_cati **mini, char *str)
{
	t_envp	*new;
	int		i;

	new = malloc(sizeof(t_envp));
	if (!new)
		return (perror("export malloc"), 0);
	new->next = NULL;
	new->var = malloc(ut_word_len(str) + 1);
	if (!new->var)
		return (perror("export malloc"), 0);
	i = -1;
	while (str[++i])
		new->var[i] = str[i];
	new->var[i] = '\0';
	env_lstaddback(&(*mini)->envp, new);
	return (1);
}