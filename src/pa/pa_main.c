/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:12:30 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/11 22:38:52 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

/*TO DO LIST:
- REWORK THE SPLIT FN TO NOT SPLIT ANYMORE BASED ON QUOTE AND SIMPLE QUOTE
- REWORK ALL THE PARSING FN FOR THE NEW SPLIT TOKEN
*/

int	mini_is_empty(t_cati *mini)
{
	t_cati	*temp;

	temp = mini;
	if (!mini)
		return (1);
	if (!temp->next && !temp->path_cmd && !temp->cmd)
		if (!temp->outfile && !temp->infile)
			return (1);
	return (0);
}

/*Call all parsing fn and send t_cati linked list to execution*/

void	parsing(char *input, t_cati **mini)
{
	t_tok	*lst;

	lst = init_token_list(input, mini);
	split_lst_operator(&lst, mini);
	expand_lst(&lst, mini);
	clean_quote(&lst, mini);
	if (lst)
	{
		check_pipe_token(&lst, mini);
		check_double_redirection(&lst, mini);
	}
	if (lst)
		parse_options(&lst, mini);
	if (*mini)
	{
		fill_node_of_pipe(*mini);
		fill_node_env(*mini);
		check_builtin(*mini);
	}
	clean_tok(&lst);
	printfmini(*mini);
	if (!mini_is_empty(*mini))
		execute(mini);
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
