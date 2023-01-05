/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_split_lst_operator.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:26:13 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/05 12:16:37 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/*Check if there is some token glue together in this string
- Return 1 if yes
- Return 0 if no*/

int	need_to_split(char *str)
{
	int	x;

	x = -1;
	while (str[++x])
	{
		if (str[x] == '\'' || str[x] == '\"')
		{
			while (str[x] && (str[x] == '\'' || str[x] == '\"'))
				x++;
		}
		if (str[x] == '|' || str[x] == '<' || str[x] == '>')
			return (1);
		else
			x++;
	}
	return (0);
}

/*Will extract the given pipe and create the next node with the pipe*/

void	extract_pipe(t_tok *node, t_tok **lst, t_cati **mini)
{
	t_tok	*result;
	t_tok	*temp;
	char	*str;
	int		x;

	str = malloc(ft_strlen(node->str));
	if (!str)
		ut_clean_parsing_n_quit(mini, lst, errno);
	str[ft_strlen(node->str)] = '\0';
	x = -1;
	printf("len = %d\n", ft_strlen(str));
	while (++x < ft_strlen(str))
		str[x] = node->str[x + 1];
	free(node->str);
	node->str = ut_strdup("|");
	if (!node->str)
		ut_clean_parsing_n_quit(mini, lst, errno);
	temp = node->next;
	result = tok_new(str, mini, lst);
	node->next = result;
	result->next = temp;
}


/*Will do the split of the current node cause some token are glue together*/

void	trigger_split_token(t_tok *node, t_tok **lst, t_cati **mini)
{
	int	x;

	x = 0;
	while (1)
	{
		if (node->str[x] == '|')
			extract_pipe(node, lst, mini);
		return ;
	}
}

/*split t_tok list based on sep*/

void	split_lst_operator(t_tok **lst, t_cati **mini)
{
	t_tok	*temp;

	temp = *lst;
	while (temp)
	{
		if (need_to_split(temp->str))
			trigger_split_token(temp, lst, mini);
		temp = temp->next;
	}
}
