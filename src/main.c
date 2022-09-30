/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 10:16:50 by bschoeff          #+#    #+#             */
/*   Updated: 2022/09/30 22:38:24 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	**array;
	int		i;

	(void)ac;
	(void)av;
	(void)env;
	array = NULL;
	array = ft_split("\techo     -nnnnnnnnnnn a nnnnnnnn\tje peux        pa  ");
	bi_echo(array);
	i = -1;
	while (--i >= 0)
		free(array[i]);
	free(array);
	return (0);
}
