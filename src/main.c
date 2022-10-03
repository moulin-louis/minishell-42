/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 10:16:50 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/03 11:25:40 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int	main(int ac, char **av, char **env)
{
	t_envp	*envp;
	char	**array;

	(void)ac;
	(void)av;
	envp = NULL;
	array = ft_split("\techo     -nnn8nnnnnnnn a nnnnnnnn\tje peux        pa  ");
	bi_echo(array);
	if (!ev_build_env(env, &envp))
		return (1);
	bi_env(envp);
	clean_env(&envp);
	return (0);
}
