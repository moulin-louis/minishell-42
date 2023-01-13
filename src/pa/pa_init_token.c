/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_init_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 10:41:05 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/13 12:25:29 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <errno.h>

int	find_len_tok(const char *str, int pos)
{
	int	result;

	result = 0;
	while (str[pos] && str[pos] != ' ' && str[pos] != '\t')
	{
		if (str[pos] == '\'' || str[pos] == '\"')
		{
			pos++;
			result++;
			while (str[pos] && str[pos] != '\'' && str[pos] != '\"')
			{
				pos++;
				result++;
			}
			pos++;
			result++;
		}
		else
		{
			result++;
			pos++;
		}
	}
	return (result);
}

/*Split simple token into node*/

void	split_token(const char *str, int *pos, t_tok **lst, t_cati **mini)
{
	int		len;
	int		ctr;
	char	*result;
	t_tok	*temp;

	len = find_len_tok(str, *pos);
	result = malloc(len + 1);
	if (!result)
		ut_clean_parsing_n_quit(mini, lst, errno);
	result[len] = '\0';
	ctr = -1;
	while (++ctr < len)
	{
		result[ctr] = str[*pos];
		(*pos)++;
	}
	temp = tok_new(result);
	if (!temp)
		ut_clean_parsing_n_quit(mini, lst, errno);
	tok_addback(lst, temp);
}

/*Create t_tok list based on user input*/

t_tok	*init_token_list(char *input, t_cati **mini)
{
	int		i;
	t_tok	*lst;

	i = 0;
	lst = NULL;
	while (input[i])
	{
		if (input[i] != ' ' && input[i] != '\t'
			&& input[i] != ':' && input[i] != '!')
			split_token(input, &i, &lst, mini);
		else
		{
			if (!input[i])
				continue ;
			i++;
		}
	}
	return (lst);
}
