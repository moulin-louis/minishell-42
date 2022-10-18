/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:12:30 by loumouli          #+#    #+#             */
/*   Updated: 2022/10/18 14:30:21 by loumouli         ###   ########.fr       */
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
	printf("infile = %s\n", mini.infile);
	printf("outfile = %s\n", mini.outfile);
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

void	fill_node_of_pipe(t_cati *mini)
{
	t_cati	*temp;

	temp = mini;
	if (temp->next != NULL && (!temp->out_append && !temp->out_trunc))
		temp->out_pipe = 1;
	temp = temp->next;
	while (temp)
	{
		if (!temp->in_file && !temp->in_heredoc)
			temp->in_pipe = 1;
		if (temp->next != NULL && (!temp->out_append && !temp->out_trunc))
				temp->out_pipe = 1;
		temp = temp->next;
	}
}

void	check_builtin(t_cati *mini)
{
	t_cati *temp;
}

void	parsing(char *input, t_cati **mini)
{
	t_tok	*lst;

	lst = init_token_list(input);
	split_lst_operator(lst);
	parse_options(&lst, mini);
	fill_node_of_pipe(*mini);
	check_builtin(*mini);
	t_cati *temp = *mini;
	while (temp)
	{
		printfmini(*temp);
		temp = temp->next;
	}
	clean_tok(&lst);
	execute(mini);
	clean_mini(mini);
}

//SI ON FAIT "'"'""'"'" JE M'ARRETE A LA PREMIERE "
//PAS BIEN
//A FIX
