/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli < loumouli@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:12:30 by loumouli          #+#    #+#             */
/*   Updated: 2022/10/09 13:57:55 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	mini_len(t_cati *mini)
{
	int		result;
	t_cati	*temp;
	
	result = 0;
	temp = mini;
	while(temp)
	{
		result++;
		temp = temp->next;
	}
	return(result);
}

void	handle_redirection(t_cati **mini)
{
	t_cati	*temp;
	t_cati	*temp2;
	int	len;
	
	len = mini_len(*mini);
	temp = *mini;
	if(len > 2 && temp->next->path_cmd[0] == '<')
	{
		temp->path_file = ut_strdup(temp->next->next->path_cmd);
		temp = (*mini)->next;
		temp2 = (*mini)->next->next;
		(*mini)->next =  (*mini)->next->next->next;
		mini_delone(temp);
		mini_delone(temp2);		
	}

}

void	parse_options(t_cati  *mini)
{
	t_cati	*temp;
	int		nbr_opt;
	char	**result;
	int		i;

	temp = mini;
	nbr_opt = 0;
	result = NULL;
	while (temp && (ft_strncmp(temp->path_cmd, "|", 2) || ft_strncmp(temp->path_cmd,
		"<", 2) || ft_strncmp(temp->path_cmd, ">", 2)))
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
}

void	parsing(char *input)
{
	t_cati	*mini;

	mini = tokenize_string(input);
	handle_redirection(&mini);
	parse_options(mini);
	t_cati *temp = mini;
	printf("%s\n", temp->path_cmd);
	if (temp->cmd)
	{
		int i = 0;
		while (temp->cmd[i])
		{
			printf("[%s]\n", temp->cmd[i]);
			i++;
		}
	}
	clean_mini(&mini);
}