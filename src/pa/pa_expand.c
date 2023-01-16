/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 15:37:24 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/16 13:24:01 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <stdlib.h>

void	delete_dollar(t_tok *node, t_tok **lst, t_cati **mini)
{
	int		len;
	int		pos;
	char	*result;

	len = ft_strlen(node->str);
	result = malloc(len);
	if (!len)
		ut_clean_parsing_n_quit(mini, lst, errno);
	result[len - 1] = '\0';
	pos = 0;
	len = 0;
	while (node->str[++len])
	{
		result[pos] = node->str[len];
		pos++;
	}
	free(node->str);
	node->str = result;
}

/*Return the value found int the environement*/

char	*find_var(char *str, char *temp1, t_cati **mini)
{
	t_envp	*temp;
	char	*result;

	temp = (*mini)->envp;
	if (ut_strcmp(str, "?"))
	{
		result = ut_itoa(g_var.g_status);
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
	result = ut_strdup("");
	if (!result)
		return (NULL);
	return (result);
}

int	insert_str(char *var, t_tok *node, t_tok **lst, t_cati **mini)
{
	char	*temp;
	char	*temp2;
	char	*temp3;
	int		len;

	temp = ut_strjoin("$", var);
	if (!temp)
	{
		free(var);
		ut_clean_parsing_n_quit(mini, lst, errno);
	}
	temp2 = find_var(var, temp, mini);
	if (!temp2)
		ut_clean_parsing_n_quit(mini, lst, errno);
	len = ft_strlen(temp2);
	temp3 = ut_strinsert(node->str, temp, temp2);
	if (!temp3)
	{
		free(var);
		ut_clean_parsing_n_quit(mini, lst, errno);
	}
	node->str = temp3;
	free(var);
	return (len);
}

/*Insert the expanded value in the string*/

int	trigger_expand(t_tok *node, int i, t_tok **lst, t_cati **mini)
{
	char	*var;
	int		len;
	int		x;

	len = find_len(node->str, i);
	if (len == 0)
	{
		delete_dollar(node, lst, mini);
		return (1);
	}
	var = malloc(len + 1);
	if (!var)
		ut_clean_parsing_n_quit(mini, lst, errno);
	var[len] = '\0';
	x = 0;
	i++;
	while (x < len)
	{
		var[x] = node->str[i];
		x++;
		i++;
	}
	return (insert_str(var, node, lst, mini));
}

/*Make the expand happened*/
void	expand_lst(t_tok **lst, t_cati **mini)
{
	t_tok	*temp;
	int		i;
	int		mode_quote;
	int		mode_dbl_quote;

	temp = *lst;
	mode_quote = 2;
	mode_dbl_quote = 2;
	while (temp)
	{
		i = -1;
		while (temp->str[++i])
		{
			if (temp->str[i] == '\"')
				mode_dbl_quote++;
			if (temp->str[i] == '\'' && !(mode_dbl_quote % 2))
				mode_quote++;
			if (temp->str[i] == '$' && !(mode_quote % 2)
				&& !(temp->str[i + 1] == '\"'))
				i += trigger_expand(temp, i, lst, mini) - 1;
		}
		temp = temp->next;
	}
}	
