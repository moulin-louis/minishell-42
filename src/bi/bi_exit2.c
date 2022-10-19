/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:29:25 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/19 14:11:17 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_neg(char *str)
{
	int		i;
	char	*negative;

	i = 0;
	negative = "-9223372036854775808";
	while (str[i] && negative[i])
	{
		if (str[i] > negative[i])
			return (0);
		i++;
	}
	return (1);
}

static int	check_pos(char *str)
{
	int		i;
	char	*positive;

	i = 0;
	positive = "9223372036854775807";
	while (str[i] && positive[i])
	{
		if (str[i] > positive[i])
			return (0);
		i++;
	}
	return (1);
}

int	ut_within_long(char *str)
{
	int		i;

	i = ut_word_len(str);
	if (str[0] == '-')
		i--;
	if (i < 19)
		return (1);
	if (i > 19)
		return (0);
	if (str[0] == '-')
		return (check_neg(str));
	else
		return (check_pos(str));
}
