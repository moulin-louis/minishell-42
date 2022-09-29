/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 12:51:41 by loumouli          #+#    #+#             */
/*   Updated: 2022/09/29 13:11:04 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	run_prompt(void)
{
	char	*u_input;

	write(1, "$> ", 3);
	while(1)
	{
		u_input = get_next_line(0);
		free(u_input);
		write(1, "$> ", 3);
	}
}
