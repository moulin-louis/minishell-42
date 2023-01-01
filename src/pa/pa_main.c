/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:12:30 by loumouli          #+#    #+#             */
/*   Updated: 2022/12/14 12:11:58 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

/*TO DO LIST :
FIX '<>' -> FIX SPLIT FOR REDIRECTION 
- FIX CTRL + C DOUBLE SHELL WHEN CAT IS RUNNING
*/

void	printfmini(t_cati *mini);
void	fill_node_of_pipe(t_cati *mini);
void	fill_node_env(t_cati *mini);
void	check_builtin(t_cati *mini);

/*Call all parsing fn and send t_cati linked list to execution*/

void	parsing(char *input, t_cati **mini)
{
	t_tok	*lst;

	lst = init_token_list(input, mini);
	split_lst_operator(&lst, mini);
	expand_lst(&lst, mini);
	clean_quote(&lst, mini);
	parse_options(&lst, mini);
	if (*mini)
	{
		fill_node_of_pipe(*mini);
		fill_node_env(*mini);
		check_builtin(*mini);
		clean_tok(&lst);
		//printfmini(*mini);
		execute(mini);
	}
	clean_mini(mini);
}

/*Print all node from t_cati list*/

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
		printf("in_fd = %d\nout_fd = %d\n", tmp->in_fd, tmp->out_fd);
		printf("fds = %p\nenvp = %p\n", & tmp->fds, & tmp->envp);
		printf("builtin = %d\nin_file = %d\n", tmp->builtin, tmp->in_file);
		printf("in_pipe = %d\nout_append = %d\n", tmp->in_pipe, tmp->out_append);
		printf("out_trunc = %d\n", tmp->out_trunc);
		printf("out_pipe = %d\nnext = %p\n\n", tmp->out_pipe, tmp->next);
		tmp = tmp->next;
	}
}

/*Fill each node with pipe flag when necessery*/

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

/*Fill each node with envp ptr*/

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

/*fill each node for builtin flag*/

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
