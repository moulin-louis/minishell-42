/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli < loumouli@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:12:30 by loumouli          #+#    #+#             */
/*   Updated: 2022/10/27 19:38:47 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

/* TO DO :
- FIX QUOTE DOUBLE QUOTE
- IMPLEMENT EXPAND */
void	printfmini(t_cati *mini);
void	fill_node_of_pipe(t_cati *mini);
void	fill_node_env(t_cati *mini);
void	check_builtin(t_cati *mini);

void	parsing(char *input, t_cati **mini)
{
	t_tok	*lst;

	lst = init_token_list(input, mini);
	split_lst_operator(&lst, mini);
	expand_lst(&lst, mini);
	parse_options(&lst, mini);
	fill_node_of_pipe(*mini);
	fill_node_env(*mini);
	check_builtin(*mini);
	clean_tok(&lst);
	execute(mini);
	clean_mini(mini);
}

void	printfmini(t_cati *mini)
{
	int		i;
	t_cati	*tmp;

	tmp = mini;
	while (tmp)
	{
		printf("path_cmd = %s\n", tmp->path_cmd);
		if (tmp->cmd)
		{
			i = -1;
			while (tmp->cmd[++i])
				printf("cmd[%d] = [%s]\t", i, tmp->cmd[i]);
			printf("\n");
		}
		printf("infile = %s\noutfile = %s\n", tmp->infile, tmp->outfile);
		printf("fds = %p\nenvp = %p\n", & tmp->fds, & tmp->envp);
		printf("builtin = %d\nin_file = %d\n", tmp->builtin, tmp->in_file);
		printf("in_pipe = %d\nout_append = %d\n", tmp->in_pipe, tmp->out_append);
		printf("out_trunc = %d\n", tmp->out_trunc);
		printf("out_pipe = %d\nnext = %p\n\n", tmp->out_pipe, tmp->next);
		tmp = tmp->next;
	}
}

void	fill_node_of_pipe(t_cati *mini)
{
	t_cati	*temp;

	temp = mini;
	if (temp->next && (!temp->out_append || !temp->out_trunc))
		temp->out_pipe = 1;
	temp = temp->next;
	while (temp)
	{
		if (temp->next && (!temp->out_append || !temp->out_trunc))
			temp->out_pipe = 1;
		if (!temp->in_file)
			temp->in_pipe = 1;
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
