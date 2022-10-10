/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_parse_options.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:55:44 by loumouli          #+#    #+#             */
/*   Updated: 2022/10/10 15:02:47 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	if (str1[i])
		return (0);
	else if (str2[i])
		return (0);
	return (1);
}

int	ft_is_sep(char *str)
{
	if (ft_strcmp(str, "|"))
		return (1);
	else if (ft_strcmp(str, "<"))
		return (1);
	else if (ft_strcmp(str, ">"))
		return (1);
	else if (ft_strcmp(str, "<<"))
		return (1);
	else if (ft_strcmp(str, ">>"))
		return (1);
	return (0);
}

void	fill_result(char **result, t_tok *lst, int nbr)
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

void	clean_lst(t_tok **lst)
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

void	parse_options(t_tok **lst, t_cati *mini)
{
	char	**result;
	int		nbr_opt;
	int		i;
	t_tok	*temp;

	i = 0;
	nbr_opt = 0;
	temp = *lst;
	while (temp && !ft_is_sep(temp->str))
	{
		nbr_opt++;
		temp = temp->next;
	}
	printf("nbr_opt = %d\n", nbr_opt);
	result = malloc(sizeof(char *) * (nbr_opt + 1));
	if (!result)
		return ;
	result[nbr_opt] = NULL;
	fill_result(result, *lst, nbr_opt);
	clean_lst(lst);
	mini->cmd = result;
}
