/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 15:37:24 by loumouli          #+#    #+#             */
/*   Updated: 2022/12/05 16:34:41 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

char	*find_var(char *str, t_tok **lst, t_cati **mini)
{
	t_envp	*temp;
	char	*result;

	temp = (*mini)->envp;
	if (ut_strcmp(str, "?"))
		return (ut_itoa(g_status, mini, lst));
	while (temp && !ut_strcmp(temp->var[0], str))
		temp = temp->next;
	if (!temp)
	{
		result = malloc(1);
		if (!result)
			ut_clean_parsing_n_quit(mini, lst, errno);
		return (result[0] = '\0', result);
	}
	result = ut_strdup(temp->var[1]);
	if (!result)
		ut_clean_parsing_n_quit(mini, lst, errno);
	return (result);
}

void	trigger_expand(t_tok *node, int i, t_tok **lst, t_cati **mini)
{
	char	*var;
	int		len;

	len = i;
	len++;
	while (node->str[len] && node->str[len] != ' ' && node->str[len] != '\"')
		len++;
	len = (len - i) - 1;
	var = malloc(len + 1);
	if (!var)
		ut_clean_parsing_n_quit(mini, lst, errno);
	var[len] = '\0';
	len = 0;
	i++;
	while (node->str[i] && node->str[i] != ' ' && node->str[i] != '\"')
	{
		var[len] = node->str[i];
		len++;
		i++;
	}
	free(node->str);
	node->str = find_var(var, lst, mini);
	free(var);
}

void	expand_lst(t_tok **lst, t_cati **mini)
{
	t_tok	*temp;
	int		i;

	temp = *lst;
	while (temp)
	{
		i = -1;
		if (temp->str[i + 1] == '\'')
			return ;
		while (temp->str[++i])
		{
			if (temp->str[i] == '$' && temp->str[i + 1])
			{
				trigger_expand(temp, i, lst, mini);
				break ;
			}
		}
		temp = temp->next;
	}
}
