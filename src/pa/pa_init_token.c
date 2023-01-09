/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_init_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 10:41:05 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/09 14:33:32 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <errno.h>

/*Split double quote token into node*/

void	split_dbl_quote(const char *str, int *i, t_tok **lst, t_cati **mini)
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
	add_new(temp, lst, mini);
}

/*Split simple quote token into node*/

void	split_quote(const char *str, int *i, t_tok **lst, t_cati **mini)
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
	add_new(temp, lst, mini);
}

/*Split simple token into node*/

void	split_token(const char *str, int *i, t_tok **lst, t_cati **mini)
{
	int		x;
	char	*temp;

	x = (*i);
	while (str[x] && (str[x] != '\t' && str[x] != ' ' && str[x]
			!= '\"' && str[x] != '\''))
		x++;
	x = x - (*i);
	temp = malloc(x + 1);
	if (!temp)
	{
		ut_clean_parsing_n_quit(mini, lst, errno);
		exit (1);
	}
	temp[x] = '\0';
	x = 0;
	while (str[*i] && (str[*i] != ' ' && str[*i] != '\t'
			&& str[*i] != '\"' && str[*i] != '\''))
	{
		temp[x] = str[*i];
		(*i)++;
		x++;
	}
	add_new(temp, lst, mini);
}

/*Create t_tok list based on user input*/

t_tok	*init_token_list(char *input, t_cati **mini)
{
	int		i;
	int		temp;
	t_tok	*lst;

	i = 0;
	lst = NULL;
	while (input[i])
	{
		if (input[i] == '\"')
		{
			temp = i;
			split_dbl_quote(input, &i, &lst, mini);
			check_flag_insert(input, temp, i, lst);
		}
		else if (input[i] == '\'')
			call_fn_init_token_2(input, &i, &lst, mini);
		else if (input[i] != ' ' && input[i] != '\t'
			&& input[i] != ':' && input[i] != '!')
			call_fn_init_token_1(input, &i, &lst, mini);
		else
			i++;
	}
	return (lst);
}
