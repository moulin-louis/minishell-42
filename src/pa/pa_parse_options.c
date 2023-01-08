/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_parse_options.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:55:44 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/08 15:47:12 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <errno.h>

/*Fill double array of option based on t_tok list*/

void	fill_result(char **result, t_tok **lst, t_cati **mini, int nbr)
{
	int		i;
	t_tok	*temp;

	i = 0;
	temp = *lst;
	while (i < nbr)
	{
		result[i] = ut_strdup(temp->str);
		if (!result[i])
		{
			clean_split(result);
			ut_clean_parsing_n_quit(mini, lst, errno);
		}
		temp = temp->next;
		i++;
	}
}

/*clean each node involved in setup_node fn*/

#include <stdio.h>

void	clean_lst(t_tok **lst)
{
	t_tok	*temp;

	while (*lst && !ut_strcmp((*lst)->str, "|"))
	{
		temp = (*lst)->next;
		tok_delone(*lst);
		*lst = temp;
	}
	if (*lst && ut_strcmp((*lst)->str, "|"))
	{
		temp = (*lst)->next;
		tok_delone(*lst);
		*lst = temp;
	}
}

/*Create node for a cmd, fill double array cmd and cmd_path, call clean fn*/

void	setup_node(t_tok **lst, t_cati *node, t_cati **mini)
{
	char	**result;
	int		nbr_opt;
	t_tok	*temp;

	nbr_opt = 0;
	if (!*lst || !lst)
		ut_clean_parsing_n_quit(mini, lst, errno);
	temp = *lst;
	while (temp && !ut_strcmp(temp->str, "|"))
	{
		nbr_opt++;
		temp = temp->next;
	}
	result = malloc(sizeof(char *) * (nbr_opt + 1));
	if (!result)
		ut_clean_parsing_n_quit(mini, lst, errno);
	result[nbr_opt] = NULL;
	fill_result(result, lst, mini, nbr_opt);
	clean_lst(lst);
	node->cmd = result;
}

#include <stdio.h>

/*find nbr of cmd, call redirection parsing fn and call fn to create node*/

void	parse_options(t_tok **lst, t_cati **mini)
{
	int		nbr_cmd;
	t_tok	*temp;

	nbr_cmd = 1;
	temp = *lst;
	while (*lst)
	{
		if (ut_strcmp((*lst)->str, "|"))
			nbr_cmd++;
		*lst = (*lst)->next;
	}
	*lst = temp;
	setup_redirection(lst, mini_lstlast(*mini), mini);
	if (*lst && *mini)
		setup_node(lst, mini_lstlast(*mini), mini);
	nbr_cmd--;
	while (*lst && *mini && nbr_cmd > 0)
	{
		printf("je fait des trucs\n");
		mini_lstaddback(mini, mini_lstnew());
		setup_redirection(lst, mini_lstlast(*mini), mini);
		setup_node(lst, mini_lstlast(*mini), mini);
		nbr_cmd--;
	}
}
