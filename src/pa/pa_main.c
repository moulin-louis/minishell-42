/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:12:30 by loumouli          #+#    #+#             */
/*   Updated: 2022/10/15 13:24:36 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

void	printfmini(t_cati mini)
{
	int	i;

	printf("cmd_path = %s\n", mini.path_cmd);
	if (mini.cmd)
	{
		i = 0;
		while (mini.cmd[i])
		{
			printf("cmd[%d] = %s\t", i, mini.cmd[i]);
			i++;
		}
		printf("\n");
	}
	printf("path_file = %s\n", mini.path_file);
	printf("builtin = %d\n", mini.builtin);
	printf("in_file = %d\n", mini.in_file);
	printf("in_heredoc = %d\n", mini.in_heredoc);
	printf("in_pipe = %d\n", mini.in_pipe);
	printf("out_append = %d\n", mini.out_append);
	printf("out_trunc = %d\n", mini.out_trunc);
	printf("out_pipe = %d\n", mini.out_pipe);
	printf("next = %p\n", mini.next);
	printf("\n");
}

void	parsing(char *input, t_cati **mini)
{
	t_tok	*lst;

	lst = init_token_list(input);
	split_lst_operator(lst);
	parse_options(&lst, mini);
	execute(mini);
	clean_mini(mini);
	clean_tok(&lst);
}

//SI ON FAIT "'"'""'"'" JE M'ARRETE A LA PREMIERE "
//PAS BIEN
//A FIX
