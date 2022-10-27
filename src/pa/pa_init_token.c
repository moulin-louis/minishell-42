/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_init_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli < loumouli@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 10:41:05 by loumouli          #+#    #+#             */
/*   Updated: 2022/10/27 19:40:15 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

void	split_dbl_quote(char *str, int *i, t_tok **lst, t_cati **mini)
{
	int		x;
	char	*temp;
	int		nbr;

	x = (*i) - 1;
	nbr = 0;
	while (str[++x] && nbr != 2)
		if (str[x] == '\"')
			nbr++;
	x = x - (*i);
	temp = malloc(x + 1);
	if (!temp)
		ut_clean_parsing_n_quit(mini, lst, errno);
	temp[x] = '\0';
	x = -1;
	nbr = 0;
	while (str[*i] && nbr != 2)
	{
		temp[++x] = str[*i];
		if (str[*i] == '\"')
			nbr++;
		(*i)++;
	}
	tok_addback(lst, tok_new(temp, mini, lst));
}

void	split_quote(char *str, int *i, t_tok **lst, t_cati **mini)
{
	int		x;
	char	*temp;
	int		nbr;

	x = (*i) - 1;
	nbr = 0;
	while (str[++x] && nbr != 2)
		if (str[x] == '\'')
			nbr++;
	x = x - (*i);
	temp = malloc(x + 1);
	if (!temp)
		ut_clean_parsing_n_quit(mini, lst, errno);
	temp[x] = '\0';
	x = -1;
	nbr = 0;
	while (str[*i] && nbr != 2)
	{
		temp[++x] = str[*i];
		if (str[*i] == '\'')
			nbr++;
		(*i)++;
	}
	tok_addback(lst, tok_new(temp, mini, lst));
}

void	split_token(char *str, int *i, t_tok **lst, t_cati **mini)
{
	int		x;
	char	*temp;

	x = (*i);
	while (str[x] && (str[x] != ' ' && str[x] != '\"' && str[x] != '\''))
		x++;
	x = x - (*i);
	temp = malloc(x + 1);
	if (!temp)
		ut_clean_parsing_n_quit(mini, lst, errno);
	temp[x] = '\0';
	x = 0;
	while (str[*i] && (str[*i] != ' ' && str[*i] != '\"' && str[*i] != '\''))
	{
		temp[x] = str[*i];
		(*i)++;
		x++;
	}
	tok_addback(lst, tok_new(temp, mini, lst));
}

t_tok	*init_token_list(char *input, t_cati **mini)
{
	int		i;
	t_tok	*lst;

	i = 0;
	lst = NULL;
	while (input[i])
	{
		if (input[i] == '\"')
			split_dbl_quote(input, &i, &lst, mini);
		else if (input[i] == '\'')
			split_quote(input, &i, &lst, mini);
		else if (input[i] != '\"' && input[i] != '\'' && input[i] != ' ')
			split_token(input, &i, &lst, mini);
		else
			i++;
	}
	return (lst);
}
