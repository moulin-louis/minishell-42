/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:12:30 by loumouli          #+#    #+#             */
/*   Updated: 2022/10/10 15:09:05 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

void	parsing(char *input, t_cati **mini)
{
	t_tok	*lst;
	//t_cati	*temp;

	lst = init_token_list(input);
	(void)mini;
	// handle_redirection(&mini);
	parse_options(&lst, *mini);
	if ((*mini)->cmd)
	{
		int i = 0;
		while ((*mini)->cmd[i])
		{
			printf("cmd[%d] = [%s]\n", i, (*mini)->cmd[i]);
			i++;
		}
	}
	execute(mini);
	clean_mini(mini);
	clean_tok(&lst);
}
