/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 12:51:41 by loumouli          #+#    #+#             */
/*   Updated: 2022/10/27 15:18:22 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <unistd.h>

static void	handle_sigint(int sig)
{
	(void)sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	ft_create_node(t_cati **mini, t_envp *envp, t_fds *fds)
{
	*mini = mini_lstnew();
	(*mini)->envp = envp;
	(*mini)->fds = fds;
}

static void	handle_sigquit(int sig, siginfo_t *info, void *context)
{
	(void)sig;
	(void)context;
	if (isatty(0))
	{
		printf("is a tty");
		return ;
	}
	else if (!isatty(0))
	{
		printf("is not a tty");
		kill(info->si_pid, SIGKILL);
		write(1, "\n", 1);
		g_status = 131;
	}
}

static void	setup_sig(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = &handle_sigint;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_sigaction = handle_sigquit;
	sigaction(SIGQUIT, &sa, NULL);
}

void	run_prompt(t_envp *envp, t_fds *fds)
{
	char	*u_input;
	t_cati	*mini;

	setup_sig();
	mini = NULL;
	while (1)
	{
		ft_create_node(&mini, envp, fds);
		u_input = readline("shellnado> ");
		if (u_input == 0)
		{
			write(1, "\n", 1);
			full_exit(&mini, 0);
		}
		if (u_input)
		{
			if (ft_strlen(u_input) > 0)
			{
				parsing(u_input, &mini);
				add_history(u_input);
			}
			free(u_input);
			clean_mini(&mini);
		}
	}
}
