/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_init_token_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:02:42 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/09 13:02:49 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <errno.h>

void	add_new(char *str, t_tok **lst, t_cati **mini)
{
	t_tok	*temp;

	temp = tok_new(str);
	if (!temp)
	{
		free(str);
		ut_clean_parsing_n_quit(mini, lst, errno);
	}
	tok_addback(lst, temp);
}

void	check_flag_insert(const char *str, int start, int end, t_tok *lst)
{
	t_tok	*temp;

	if (start > 0 && str[start - 1] != ' ' && str[start - 1] != '\t')
	{
		temp = tok_last(lst);
		temp->flag_insert = 1;
	}
	(void)end;
}

void	call_fn_init_token_1(char *str, int *i, t_tok **lst, t_cati **mini)
{
	int	temp;

	temp = *i;
	split_token(str, i, lst, mini);
	check_flag_insert(str, temp, *i, *lst);
}

void	call_fn_init_token_2(char *str, int *i, t_tok **lst, t_cati **mini)
{
	int	temp;

	temp = *i;
	split_quote(str, i, lst, mini);
	check_flag_insert(str, temp, *i, *lst);
}
