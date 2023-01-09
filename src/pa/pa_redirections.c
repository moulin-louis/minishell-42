/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 13:26:36 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/07 21:46:00 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Search for redir and trigger the right fn for it*/

int	find_redir(t_tok **lst, t_tok *dest, t_cati *node, t_cati **mini)
{
	if (ut_strcmp((dest)->str, "<"))
		return (in_redir(dest, node, lst, mini), 1);
	else if (ut_strcmp((dest)->str, ">"))
		return (out_redir(dest, node, lst, mini), 1);
	else if (ut_strcmp((dest)->str, "<<"))
		return (heredoc_redir(dest, node, lst, mini), 1);
	else if (ut_strcmp((dest)->str, ">>"))
		return (app_redir(dest, node, lst, mini), 1);
	else
		return (0);
}

/*main redir fn*/

void	setup_redirection(t_tok **lst, t_cati *node, t_cati **mini)
{
	t_tok	*temp;

	temp = *lst;
	while (lst && temp && !ut_strcmp(temp->str, "|"))
	{
		if (find_redir(lst, temp, node, mini))
			temp = *lst;
		else
			temp = temp->next;
	}
}
