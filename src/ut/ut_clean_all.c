/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_clean_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 12:36:37 by bschoeff          #+#    #+#             */
/*   Updated: 2022/12/10 17:02:09 by loumouli         ###   ########.fr       */
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

/*All the cleaning stuff*/

/*exit fn used in parsing, print why malloc failed, clean t_tok and t_cati
linked list and quit the process with ernno exit code*/

void	ut_clean_parsing_n_quit(t_cati **mini, t_tok **lst, int error)
{
	perror("Malloc :");
	clean_tok(lst);
	full_exit(mini, error);
}

/*Clean a double array NULL terminated*/

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

/*Clean t_cati linked list*/

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

/*exit the process with i error code and clean mini linked list first*/

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
