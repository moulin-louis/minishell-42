/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli < loumouli@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 12:51:41 by loumouli          #+#    #+#             */
/*   Updated: 2022/10/08 15:51:31 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <unistd.h>

void	handle_sigint(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	do_nothing(int sig)
{
	(void)sig;
}

void	run_prompt(void)
{
	struct sigaction	sa;
	char				*u_input;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = &handle_sigint;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = &do_nothing;
	sigaction(SIGQUIT, &sa, NULL);
	while (1)
	{
		u_input = readline("minishell> ");
		if (u_input == 0)
		{
			rl_clear_history();
			exit(1);
		}
		if (u_input)
		{
			parsing(u_input);
			if (ft_strlen(u_input) > 0)
				add_history(u_input);
			free(u_input);
		}
	}
}
