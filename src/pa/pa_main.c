/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:12:30 by loumouli          #+#    #+#             */
/*   Updated: 2022/10/24 14:24:25 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

void	printfmini(t_cati *mini)
{
	int		i;
	t_cati	*temp;

	temp = mini;
	while (temp)
	{
		printf("path_cmd = %s\n", mini->path_cmd);
		if (mini->cmd)
		{
			i = -1;
			while (mini->cmd[++i])
				printf("cmd[%d] = [%s]\t", i, mini->cmd[i]);
			printf("\n");
		}
		printf("infile = %s\noutfile = %s\n", mini->infile, mini->outfile);
		printf("fds = %p\nenvp = %p\n", & mini->fds, & mini->envp);
		printf("builtin = %d\n", mini->builtin);
		printf("in_file = %d\nin_pipe = %d\n", mini->in_file, mini->in_pipe);
		printf("out_append = %d\n", mini->out_append);
		printf("out_trunc = %d\n", mini->out_trunc);
		printf("out_pipe = %d\n", mini->out_pipe);
		printf("next = %p\n", mini->next);
		printf("\n");
		temp = temp->next;
	}
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
		if (temp->next != NULL && (!temp->out_append && !temp->out_trunc))
				temp->out_pipe = 1;
		temp = temp->next;
	}
}

void	fill_node_env(t_cati *mini)
{
	t_fds	*fds;
	t_envp	*envp;
	t_cati	*temp;

	temp = mini;
	envp = temp->envp;
	fds = temp->fds;
	temp = temp->next;
	while (temp)
	{
		temp->envp = envp;
		temp->fds = fds;
		temp = temp->next;
	}
}

void	check_builtin(t_cati *mini)
{
	t_cati	*temp;

	temp = mini;
	while (temp)
	{
		if (temp->cmd)
		{
			if (ut_strcmp(temp->cmd[0], "export")
				|| ut_strcmp(temp->cmd[0], "echo")
				|| ut_strcmp(temp->cmd[0], "env")
				|| ut_strcmp(temp->cmd[0], "exit")
				|| ut_strcmp(temp->cmd[0], "pwd")
				|| ut_strcmp(temp->cmd[0], "cd")
				|| ut_strcmp(temp->cmd[0], "unset"))
				temp->builtin = 1;
		}
		temp = temp->next;
	}
}

void	parsing(char *input, t_cati **mini)
{
	t_tok	*lst;

	lst = init_token_list(input, mini);
	split_lst_operator(lst, mini);
	expand_lst(&lst, mini, (*mini)->envp);
	parse_options(&lst, mini);
	fill_node_of_pipe(*mini);
	fill_node_env(*mini);
	check_builtin(*mini);
	clean_tok(&lst);
	printfmini(*mini);
	execute(mini);
	clean_mini(mini);
}

/*
TO DO :
- ERROR MANEGEMENT
- FIX QUOTE DOUBLE QUOTE
- IMPLEMENT EXPAND
*/
