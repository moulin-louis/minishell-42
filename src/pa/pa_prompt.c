/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 12:51:41 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/13 12:26:27 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>

/*Handle sigint signal : CTRL + C*/

void	handle_sigint(int sig)
{
	(void)sig;
	if (g_pid != 1 && g_pid != 0)
	{
		kill(g_pid, SIGINT);
		printf("\n");
	}
	else
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

/*Handle sigint and ignore sigquit*/

void	setup_sig(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = &handle_sigint;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

/*Create a new t_cati node and return its ptr, quit minishell if fail*/

t_cati	*mini_lstnew_custom(void)
{
	t_cati	*result;

	result = ut_calloc(1, sizeof(t_cati));
	if (!result)
		return (NULL);
	return (result);
}

/*Create first node of t_cati list*/

void	ft_create_node(t_cati **mini, t_envp *envp, t_fds *fds)
{
	*mini = mini_lstnew_custom();
	if (!(*mini))
	{
		env_lstclear(&envp);
		perror("shellnado");
		full_exit(mini, errno);
	}
	(*mini)->envp = envp;
	(void)fds;
}

/*init prompt with rl and call parsing fn when needed*/

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
		}
	}
}
