/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ev_build_env2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:21:42 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/13 14:38:59 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int	set_new1(t_envp *new1)
{
	new1->var = malloc(3 * sizeof(char *));
	new1->var[0] = malloc(7);
	new1->var[0] = "OLDPWD";
	new1->var[1] = NULL;
	new1->var[2] = NULL;
	return (1);
}

int	set_new2(t_envp *new2)
{
	new2->var = malloc(3 * sizeof(char *));
	new2->var[0] = malloc(4);
	new2->var[0] = "PWD";
	new2->var[1] = malloc(5);
	new2->var[1] = "/mnt";
	new2->var[2] = NULL;
	return (1);
}

int	set_new3(t_envp *new3)
{
	new3->var = malloc(3 * sizeof(char *));
	new3->var[0] = malloc(6);
	new3->var[0] = "SHLVL";
	new3->var[1] = malloc(2);
	new3->var[1] = "1";
	new3->var[2] = NULL;
	return (1);
}
