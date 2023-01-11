/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_expand_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:52:10 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/11 16:54:36 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_len(char *str, int i)
{
	int	result;

	result = i + 1;
	if (str[result] == '?')
		return (1);
	if (ft_isnum(str[result]) || !ft_isalpha(str[result]))
		return (0);
	while (ft_isalpha(str[result]) || ft_isnum(str[result]))
		result++;
	result = (result - i) - 1;
	return (result);
}
