/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 13:26:36 by loumouli          #+#    #+#             */
/*   Updated: 2022/10/17 15:48:55 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_redir(char *str)
{
	if (ut_strcmp(str, "<") || ut_strcmp(str, ">") || ut_strcmp(str, ">>"))
		return (1);
	if (ut_strcmp(str, "<<"))
		return (1);
	return (0);
}

void	find_redir(t_tok **lst, t_tok *dest, t_cati *mini)
{
	if (ut_strcmp((*lst)->str, "<"))
		in_redir(lst, dest, mini);
	// else if (ut_strcmp((*lst)->str, ">"))
	// 	out_redir(lst, mini);
	// else if (ut_strcmp((*lst)->str, "<<"))
	// 	heredoc_redir(lst, mini);
	// else if (ut_strcmp((*lst)->str, ">>"))
	// 	append_redir(lst, mini);
}

void	setup_redirection(t_tok **lst, t_cati *mini)
{
	t_tok	*temp;

	temp = *lst;
	while (temp)
	{
		if (ft_is_redir(temp->str))
			find_redir(lst, temp, mini);
		temp = temp->next;
	}
}
