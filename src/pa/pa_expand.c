/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 15:37:24 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/09 15:00:21 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <stdlib.h>

/*Return the value found int the environement*/

char	*find_var(char *str, char *temp1, t_cati **mini)
{
	t_envp	*temp;
	char	*result;

	temp = (*mini)->envp;
	if (ut_strcmp(str, "?"))
	{
		result = ut_itoa(g_status);
		if (!result)
			return (free(str), free(temp1), NULL);
		return (result);
	}
	while (temp && !ut_strcmp(temp->var[0], str))
		temp = temp->next;
	if (temp)
	{
		result = ut_strdup(temp->var[1]);
		if (!result)
			return (free(str), free(temp1), NULL);
		return (result);
	}
	return (NULL);
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

void	insert_str(char *var, t_tok *node, t_tok **lst, t_cati **mini)
{
	char	*temp;
	char	*temp2;
	char	*temp3;

	temp = ut_strjoin("$", var);
	if (!temp)
	{
		free(var);
		ut_clean_parsing_n_quit(mini, lst, errno);
		exit (1);
	}
	temp2 = find_var(var, temp, mini);
	if (!temp2)
		ut_clean_parsing_n_quit(mini, lst, errno);
	temp3 = ut_strinsert(node->str, temp, temp2);
	if (!temp3)
	{
		free(var);
		ut_clean_parsing_n_quit(mini, lst, errno);
		exit (1);
	}
	node->str = temp3;
	free(var);
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
	{
		ut_clean_parsing_n_quit(mini, lst, errno);
		exit (1);
	}
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
	insert_str(var, node, lst, mini);
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
