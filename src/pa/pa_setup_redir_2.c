/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_setup_redir_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 22:35:33 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/13 12:26:49 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

void	check_file(char *str, t_cati *node, t_tok **lst, t_cati **mini)
{
	int	fd;

	stat(str, &node->buff);
	if (S_ISDIR(node->buff.st_mode))
	{
		ut_putstr_fd("bash : ", 2);
		ut_putstr_fd(str, 2);
		ut_putstr_fd(": Is a directory\n", 2);
		reset_ressources(lst, mini);
		return ;
	}
	fd = open(str, O_RDONLY | O_CREAT, 0644);
	if (fd == -1)
	{
		perror(str);
		reset_ressources(lst, mini);
		return ;
	}
	close(fd);
}
