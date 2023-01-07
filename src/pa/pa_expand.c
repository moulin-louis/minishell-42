/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 15:37:24 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/07 21:47:41 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <stdlib.h>

/*Return the value found int the environement*/

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

int	find_len(char *str, int i)
{
	int	result;

	result = i + 1;
	if (str[result] == '?')
		return (1);
	if ((str[result] >= '0' && str[result] <= '9') || !ft_isalpha(str[result]))
		return (0);
	while (ft_isalpha(str[result]) || (str[result] >= '0'
			&& str[result] <= '9'))
		result++;
	result = (result - i) - 1;
	return (result);
}

/*Insert the expanded value in the string*/

void	trigger_expand(t_tok *node, int i, t_tok **lst, t_cati **mini)
{
	char	*var;
	int		len;

	len = find_len(node->str, i);
	if (len == 0)
		return ;
	var = malloc(len + 1);
	if (!var)
		ut_clean_parsing_n_quit(mini, lst, errno);
	var[len] = '\0';
	len = 0;
	i++;
	while (node->str[i] && (node->str[i] == '?' || ft_isalphanum(node->str[i]))
		&& node->str[i] != ' ' && node->str[i] != '\"')
	{
		var[len] = node->str[i];
		len++;
		i++;
	}
	node->str = ut_strinsert(node->str, ut_strjoin("$", var),
			find_var(var, lst, mini));
	if (!node->str)
		ut_clean_parsing_n_quit(mini, lst, errno);
	free(var);
}

/*Make the expand happened*/

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
				trigger_expand(temp, i, lst, mini);
		}
		temp = temp->next;
	}
}
