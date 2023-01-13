/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_split_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 19:42:18 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/13 12:27:27 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <stdlib.h>

int	len_next_tok(const char *str, int pos)
{
	int	result;

	result = 0;
	if (str[pos] != '|' && str[pos] != '<' && str[pos] != '>')
	{
		while (str[pos] && (str[pos] != '|' && str[pos] != '<' && str[pos]
				!= '>'))
		{
			pos++;
			result++;
		}
		return (result);
	}
	if (str[pos] == '|' || (str[pos] == '>' && (str[pos + 1]
				&& str[pos + 1] != '>')) || (str[pos] == '<'
			&& (str[pos + 1] && str[pos + 1] != '<')))
		return (1);
	else
		return (2);
	return (result);
}

char	*create_string(const char *str, int *pos)
{
	int		len;
	char	*result;
	int		x;

	x = 0;
	len = len_next_tok(str, *pos);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	result[len] = '\0';
	while (x < len)
	{
		result[x] = str[*pos];
		(*pos)++;
		x++;
	}
	return (result);
}

char	**split_tok(const char *str, int nbr_tok, t_tok **lst, t_cati **mini)
{
	char	**result;
	int		x;
	int		pos_string;

	x = 0;
	pos_string = 0;
	result = malloc(sizeof(char *) * (nbr_tok + 1));
	if (!result)
	{
		ut_clean_parsing_n_quit(mini, lst, errno);
		exit (1);
	}
	result[nbr_tok] = NULL;
	while (x < nbr_tok)
	{
		result[x] = create_string(str, &pos_string);
		if (!result[x])
		{
			clean_split(result);
			ut_clean_parsing_n_quit(mini, lst, errno);
		}
		x++;
	}
	return (result);
}
