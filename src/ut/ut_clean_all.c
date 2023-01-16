/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_clean_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 12:36:37 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/16 17:10:13 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*   Updated: 2022/12/08 18:11:42 by foster           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <errno.h>
#include <readline/readline.h>
#include <unistd.h>

/*All the cleaning stuff*/

/*exit fn used in parsing, print why malloc failed, clean t_tok and t_cati
linked list and quit the process with ernno exit code*/

void	ut_clean_parsing_n_quit(t_cati **mini, t_tok **lst, int error)
{
	perror("Malloc :");
	clean_tok(lst);
	full_exit(mini, error);
}

/*Clean lst and cati linked list and put the ptr to NULL*/

void	reset_ressources(t_tok **lst, t_cati **mini)
{
	clean_tok(lst);
	clean_mini(mini);
	*lst = NULL;
	*mini = NULL;
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
	(void) i;
	if (mini && *mini)
	{
		if ((*mini)->envp)
			env_lstclear(&(*mini)->envp);
		clean_mini(mini);
	}
	rl_clear_history();
	exit (i);
}
