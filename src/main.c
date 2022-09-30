/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 10:16:50 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/01 00:08:52 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int	main(int ac, char **av, char **env)
{
	t_envp	*envp;
	char	**array;
	int		i;

	(void)ac;
	(void)av;
	envp = NULL;
	array = ft_split("\techo     -nnnnnnnnnnn a nnnnnnnn\tje peux        pa  ");
	bi_echo(array);
	if (!ev_build_env(env, &envp))
		return (1);
	i = -1;
	/*while ((*envp).envp[++i])
		printf("%s\n", (*envp).envp[i]);*/
	return (0);
}
