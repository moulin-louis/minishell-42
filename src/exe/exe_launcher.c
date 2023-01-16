/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_launcher.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:43:55 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/16 17:10:11 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exe_bi_launcher(t_cati **mini, t_cati *node)
{
	if (ut_strcmp("cd", node->cmd[0]))
		return (bi_cd(mini, node));
	else if (ut_strcmp("echo", node->cmd[0]))
		return (bi_echo(node));
	else if (ut_strcmp("env", node->cmd[0]))
		return (bi_env(mini));
	else if (ut_strcmp("pwd", node->cmd[0]))
		return (bi_pwd(node));
	else if (ut_strcmp("export", node->cmd[0]))
		return (bi_export(node));
	else if (ut_strcmp("exit", node->cmd[0]))
		return (bi_exit(mini, node));
	else if (ut_strcmp("unset", node->cmd[0]))
		return (bi_unset(mini, node));
	return (0);
}
