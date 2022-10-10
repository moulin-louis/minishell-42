/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:12:30 by loumouli          #+#    #+#             */
/*   Updated: 2022/10/10 11:51:40 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

void	handle_redirection(t_cati **mini)
{
	t_cati	*temp;
	t_cati	*temp2;
	int		len;

	len = mini_len(*mini);
	temp = *mini;
	if (len > 2 && temp->next->path_cmd[0] == '<')
	{
		temp->path_file = ut_strdup(temp->next->next->path_cmd);
		temp = (*mini)->next;
		temp2 = (*mini)->next->next;
		(*mini)->next = (*mini)->next->next->next;
		mini_delone(temp);
		mini_delone(temp2);
	}
}

int	ft_is_sep(char *str)
{
	if (ft_strncmp(str, "|", 2))
		return (1);
	if (ft_strncmp(str, "<", 2))
		return (1);
	if (ft_strncmp(str, ">", 2))
		return (1);
	if (ft_strncmp(str, "<<", 3))
		return (1);
	if (ft_strncmp(str, ">>", 3))
		return (1);
	return (0);
}

void	parse_options(t_cati *mini)
{
	t_cati	*temp;
	int		nbr_opt;
	char	**result;
	int		i;

	temp = mini;
	nbr_opt = 0;
	result = NULL;
	while (temp && ft_is_sep(temp->path_cmd))
	{
		nbr_opt++;
		temp = temp->next;
	}
	result = malloc(sizeof(char *) * (nbr_opt + 1));
	if (!result)
		return ;
	result[nbr_opt] = NULL;
	i = 0;
	temp = mini;
	while (i < nbr_opt)
	{
		result[i] = ut_strdup(temp->path_cmd);
		if (!result[i])
			return ;
		temp = temp->next;
		i++;
	}
	mini->cmd = result;
	i = 1;
	temp = mini->next;
	t_cati *temp2;
	while (i < nbr_opt)
	{
		temp2 = temp->next;
		free(temp);
		temp = temp2;
		i++;
	}
	mini->next = NULL;
}

void	init_env_fd(t_cati *mini, t_envp *envp, t_envp *expt_ev, t_fds *fds)
{
	t_cati	*temp;

	temp = mini;
	while (temp)
	{
		temp->envp = envp;
		temp->expt_ev = expt_ev;
		temp->fds = fds;
		temp = temp->next;
	}
}

void	parsing(char *input, t_envp *envp, t_envp *expt_ev, t_fds *fds)
{
	t_cati	*mini;

	mini = tokenize_string(input);
	handle_redirection(&mini);
	parse_options(mini);
	init_env_fd(mini, envp, expt_ev, fds);
	execute(&mini);
	clean_mini(&mini);
}
