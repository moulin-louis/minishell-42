/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_clean_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 12:36:37 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/27 12:12:20 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>

void	ut_clean_parsing_n_quit(t_cati **mini, t_tok **lst, int error)
{
	perror("Malloc :");
	clean_tok(lst);
	full_exit(mini, error);
}

void	clean_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

void	clean_mini(t_cati **mini)
{
	t_cati	*tmp;

	if (!*mini)
		return ;
	while (*mini)
	{
		tmp = *mini;
		*mini = (*mini)->next;
		if (tmp->cmd)
			clean_split(tmp->cmd);
		if (tmp->ev)
			clean_split(tmp->ev);
		if (tmp->path_cmd)
			free(tmp->path_cmd);
		if (tmp->infile)
			free(tmp->infile);
		if (tmp->outfile)
			free(tmp->outfile);
		if (tmp->in_fd > 2)
			close(tmp->in_fd);
		if (tmp->out_fd > 2)
			close(tmp->out_fd);
		free(tmp);
	}
	unlink("/tmp/.heredoc.tmp");
}

void	full_exit(t_cati **mini, int i)
{
	if (mini && *mini)
	{
		if ((*mini)->envp)
			env_lstclear(&(*mini)->envp);
		clean_mini(mini);
	}
	rl_clear_history();
	exit (i);
}
