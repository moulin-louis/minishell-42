/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 13:26:36 by loumouli          #+#    #+#             */
/*   Updated: 2022/10/24 14:20:26 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int	ft_is_redir(char *str)
{
	if (ut_strcmp(str, "<") || ut_strcmp(str, ">") || ut_strcmp(str, ">>"))
		return (1);
	if (ut_strcmp(str, "<<"))
		return (1);
	return (0);
}

void	find_redir(t_tok **lst, t_tok *dest, t_cati *node, t_cati **mini)
{
	if (ut_strcmp((dest)->str, "<"))
		in_redir(lst, dest, node, mini);
	else if (ut_strcmp((dest)->str, ">"))
		out_redir(lst, dest, node, mini);
	else if (ut_strcmp((dest)->str, "<<"))
		heredoc_redir(lst, dest, node, mini);
	else if (ut_strcmp((dest)->str, ">>"))
		append_redir(lst, dest, node, mini);
}

void	setup_redirection(t_tok **lst, t_cati *node, t_cati **mini)
{
	t_tok	*temp;

	temp = *lst;
	while (temp && !ut_strcmp(temp->str, "|"))
	{
		if (ft_is_redir(temp->str))
		{
			find_redir(lst, temp, node, mini);
			temp = *lst;
		}
		else
			temp = temp->next;
	}
}
