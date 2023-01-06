/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:12:30 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/06 13:47:21 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

/*TO DO LIST :
- IMPLEMENT ERROR MANAGEMENT PIPE
- FIX PARSING ">>>>>>" AND "<<<<<<<"
- FIX EXPAND READ VAR
- FIX CTRL + C DOUBLE SHELL WHEN CAT IS RUNNING
*/

/*Ugly function to check if there is a < > in my linked list of token*/

void	check_double_redirection(t_tok **lst, t_cati **mini)
{
	t_tok	*temp;

	temp = *lst;
	while (temp)
	{
		if (ut_strcmp(temp->str, "<") && (temp->next
				&& ut_strcmp(temp->next->str, ">")))
		{
			printf("shellnado : invalid token syntax near '\\n'\n");
			reset_ressources(lst, mini);
			g_status = 2;
			return ;
		}
		temp = temp->next;
	}
}

/*Call all parsing fn and send t_cati linked list to execution*/

void	parsing(char *input, t_cati **mini)
{
	t_tok	*lst;

	lst = init_token_list(input, mini);
	split_lst_operator(&lst, mini);
	expand_lst(&lst, mini);
	clean_quote(&lst, mini);
	check_double_redirection(&lst, mini);
	if (lst && *mini)
		parse_options(&lst, mini);
	if (*mini)
	{
		fill_node_of_pipe(*mini);
		fill_node_env(*mini);
		check_builtin(*mini);
		clean_tok(&lst);
		execute(mini);
	}
	clean_mini(mini);
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
	t_envp	*envp;
	t_cati	*temp;

	temp = mini;
	envp = temp->envp;
	temp = temp->next;
	while (temp)
	{
		temp->envp = envp;
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
