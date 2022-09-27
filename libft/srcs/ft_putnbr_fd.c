/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:59:13 by loumouli          #+#    #+#             */
/*   Updated: 2022/05/06 17:56:40 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	lg;

	lg = n;
	if (lg < 0)
	{
		lg = lg * -1;
		ft_putchar_fd('-', fd);
	}
	if (lg >= 10)
	{
		ft_putnbr_fd(lg / 10, fd);
		ft_putnbr_fd(lg % 10, fd);
	}
	if ((lg >= 0) && (lg < 10))
	{
		ft_putchar_fd(lg + '0', fd);
	}
}
