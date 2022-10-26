/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_init_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 13:51:27 by loumouli          #+#    #+#             */
/*   Updated: 2022/10/26 16:15:19 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void	spplit_dbl_quote(char *str, int *i, t_tok **result, t_cati **mini)
{
	int		x;
	char	*temp;

	x = *i;
	while (str[x])
		x++;
	x = x - *i;
	temp = malloc(x + 1);
	if (!temp)
		ut_clean_parsing_n_quit(mini, result, errno);
	x = 0;
	while (str[*i] && str[*i] != '\"')
	{
		temp[x] = str[*i];
		x++;
		*i++;
	}
	tok_addback(result, tok_new(temp));
}

t_tok	*init_token_list(char *input, t_cati **mini)
{
	int		i;
	t_tok	*result;

	i = -1;
	while(input[++i])
	{
		if (input[i] == '\"')
			split_dbl_quote(input, &i, &result, mini);
	}
	return (result);
}
