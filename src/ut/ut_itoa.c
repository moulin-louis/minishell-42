/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 19:55:11 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/09 14:59:30 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <errno.h>

/*Return the len of the nbr*/

static	int	ft_size_nbr(long nbr)
{
	int	result_nbr;

	result_nbr = 0;
	if (nbr == 0)
		return (1);
	while (nbr > 1)
	{
		nbr /= 10;
		result_nbr++;
	}
	if (nbr == 1)
		result_nbr++;
	return (result_nbr);
}

/*Fill the string based on the nbr, the sign and the len of the nbr*/

static	void	ft_fill_result(char *result, int size_nbr, long nbr, int minus)
{
	if (minus == 1)
	{
		result[0] = '-';
		while (size_nbr != 0)
		{
			result[size_nbr] = (nbr % 10) + '0';
			nbr /= 10;
			size_nbr--;
		}
	}
	if (minus == 0)
	{
		size_nbr--;
		while (size_nbr >= 0)
		{
			result[size_nbr] = (nbr % 10) + '0';
			nbr /= 10;
		size_nbr--;
		}
	}
}

/*Add the null char based on the sign of the number*/

static	void	ft_add_null_terminal_number(char *result, int size_nbr,
		int minus)
{
	if (minus == 1)
		result[size_nbr + 1] = '\0';
	if (minus == 0)
		result[size_nbr] = '\0';
}

/*Handle the case if n = 0*/

static	char	*ft_nbr_0(char *result)
{
	result[0] = '0';
	result[1] = 0;
	return (result);
}

/*Convert an int into a null terminated string
Quit minishell if malloc failed*/

char	*ut_itoa(int n)
{
	long	nbr;
	int		size_nbr;
	char	*result;
	int		minus;

	nbr = n;
	minus = 0;
	if (nbr < 0)
	{
		nbr = nbr * -1;
		minus = 1;
	}
	size_nbr = ft_size_nbr(nbr);
	result = malloc(sizeof(char) * ((size_nbr + minus) + 1));
	if (!result)
		return (NULL);
	if (nbr == 0)
		return (ft_nbr_0(result));
	ft_fill_result(result, size_nbr, nbr, minus);
	ft_add_null_terminal_number(result, size_nbr, minus);
	return (result);
}
