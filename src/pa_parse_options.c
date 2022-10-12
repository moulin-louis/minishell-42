/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_parse_options.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:55:44 by loumouli          #+#    #+#             */
/*   Updated: 2022/10/12 11:50:27 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

static int	ft_is_sep(char *str)
{
	if (ut_strcmp(str, "|") || ut_strcmp(str, ">") || ut_strcmp(str, ">>"))
		return (1);
	if (ut_strcmp(str, "<") || ut_strcmp(str, "<<"))
		return (1);
	return (0);
}

static void	fill_result(char **result, t_tok *lst, int nbr)
{
	int		i;
	t_tok	*temp;

	i = 0;
	temp = lst;
	while (i < nbr)
	{
		result[i] = ut_strdup(temp->str);
		temp = temp->next;
		i++;
	}
}

static void	clean_lst(t_tok **lst)
{
	t_tok	*temp;

	temp = *lst;
	while (*lst && !ft_is_sep((*lst)->str))
	{
		temp = (*lst)->next;
		tok_delone(*lst);
		*lst = temp;
	}
	if (*lst && ft_is_sep((*lst)->str))
	{
		temp = (*lst)->next;
		tok_delone(*lst);
		*lst = temp;
	}
}

static void	setup_node(t_tok **lst, t_cati *mini)
{
	char	**result;
	int		nbr_opt;
	t_tok	*temp;

	nbr_opt = 0;
	temp = *lst;
	while (temp && !ft_is_sep(temp->str))
	{
		nbr_opt++;
		temp = temp->next;
	}
	result = malloc(sizeof(char *) * (nbr_opt + 1));
	if (!result)
		return ;
	result[nbr_opt] = NULL;
	fill_result(result, *lst, nbr_opt);
	clean_lst(lst);
	mini->cmd = result;
	mini->path_cmd = ut_strdup(mini->cmd[0]);
}

void	parse_options(t_tok **lst, t_cati **mini)
{
	int		nbr_cmd;
	t_tok	*temp;

	nbr_cmd = 1;
	temp = *lst;
	while (temp)
	{
		if (ft_is_sep(temp->str))
			nbr_cmd++;
		temp = temp->next;
	}
	setup_node(lst, mini_lstlast(*mini));
	nbr_cmd--;
	while (nbr_cmd > 0)
	{
		mini_lstaddback(mini, mini_lstnew());
		setup_node(lst, mini_lstlast(*mini));
		nbr_cmd--;
	}
}
