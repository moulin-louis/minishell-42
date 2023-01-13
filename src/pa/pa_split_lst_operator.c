/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_split_lst_operator.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:26:13 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/13 12:27:17 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <errno.h>

/*Return the nbr ok token in the string*/

int	search_tok(char *str)
{
	int	nbr_tok;

	nbr_tok = 0;
	while (*str)
	{
		if ((*str == '<' && *(str + 1) == '<')
			|| (*str == '>' && *(str + 1) == '>'))
		{
			str += 2;
			nbr_tok++;
		}
		else if (*str == '<' || *str == '>' || *str == '|')
		{
			str++;
			nbr_tok++;
		}
		else
		{
			while (*str && (*str != '<' && *str != '>' && *str != '|'))
				str++;
			nbr_tok++;
		}
	}
	return (nbr_tok);
}

t_tok	*check_create_node(char *str, char **result, t_tok **lst, t_cati **mini)
{
	t_tok	*temp;

	if (!str)
	{
		clean_split(result);
		ut_clean_parsing_n_quit(mini, lst, errno);
	}
	temp = tok_new(str);
	if (!temp)
	{
		free(str);
		clean_split(result);
		ut_clean_parsing_n_quit(mini, lst, errno);
	}
	return (temp);
}

void	fill_node_of_result(char **result, t_tok *node,
		t_tok **lst, t_cati **mini)
{
	t_tok	*temp;
	t_tok	*new_node;
	char	*str;
	int		x;

	x = 1;
	while (result[x + 1])
		x++;
	free(node->str);
	node->str = ut_strdup(result[0]);
	if (!node->str)
	{
		clean_split(result);
		ut_clean_parsing_n_quit(mini, lst, errno);
	}
	while (x)
	{
		str = ut_strdup(result[x]);
		new_node = check_create_node(str, result, lst, mini);
		temp = node->next;
		node->next = new_node;
		new_node->next = temp;
		x--;
	}
	clean_split(result);
}

void	trigger_split(t_tok *node, t_tok **lst, t_cati **mini)
{
	char	**result;
	int		nbr_tok;

	nbr_tok = search_tok(node->str);
	if (nbr_tok == 1 || nbr_tok == 0)
		return ;
	result = split_tok(node->str, nbr_tok, lst, mini);
	fill_node_of_result(result, node, lst, mini);
}

void	split_lst_operator(t_tok **lst, t_cati **mini)
{
	t_tok	*temp;

	temp = *lst;
	while (temp)
	{
		if (temp->str[0] == '\'' || temp->str[0] == '\"')
		{
			temp = temp->next;
			continue ;
		}
		trigger_split(temp, lst, mini);
		temp = temp->next;
	}
}
