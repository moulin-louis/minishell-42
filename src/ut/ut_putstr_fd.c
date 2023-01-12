/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 17:03:16 by foster            #+#    #+#             */
/*   Updated: 2023/01/12 12:38:54 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

void	ut_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

void	ut_cmd_not_found(char *s)
{
	ut_putstr_fd("bash: ", 2);
	ut_putstr_fd(s, 2);
	ut_putstr_fd(": command not found", 2);
	ut_putstr_fd("\n", 2);
}
