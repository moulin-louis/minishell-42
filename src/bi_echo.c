/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 11:20:35 by bschoeff          #+#    #+#             */
/*   Updated: 2022/09/29 12:23:24 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static 

int	bi_echo(char **args)
{
	int	i;
	int	j;
	int	len;
	int	n_line;

	i = -1;
	n_line = 0;
	while (args[++i])
		if (is_arg(args[i]))
			n_line = 1;
}
