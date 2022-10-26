/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_init_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 10:41:05 by loumouli          #+#    #+#             */
/*   Updated: 2022/10/26 17:03:56 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

void	split_dbl_quote(char *str, int *i, t_tok **result, t_cati **mini)
{
	int		x;
	char	*temp;
	int		nbr;

	x = (*i) + 1;
	while (str[x] && str[x -1] != '\"')
		x++;
	x = x - *i;
	temp = malloc(x + 1);
	if (!temp)
		ut_clean_parsing_n_quit(mini, result, errno);
	temp[x] = '\0';
	x = 0;
	if (str[*i] && str[*i] == '\"')
		temp[x] = str[*i];
	t_tok *temp2 = tok_new(temp, mini, result);
	tok_addback(result, temp2);
}

t_tok	*init_token_list(char *input, t_cati **mini)
{
	int		i;
	t_tok	*result;

	i = 0;
	result = NULL;
	while(input[i])
	{
		if (input[i] == '\"')
			split_dbl_quote(input, &i, &result, mini);
		else
			i++;
	}
	return (result);
}
