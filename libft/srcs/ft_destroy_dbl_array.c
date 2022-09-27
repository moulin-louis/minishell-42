/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_destroy_dbl_array.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 16:46:28 by loumouli          #+#    #+#             */
/*   Updated: 2022/09/05 16:47:33 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_destroy_dbl_array(char **temp)
{
	int	x;

	x = -1;
	while (temp[++x])
		free(temp[x]);
	free(temp);
}
