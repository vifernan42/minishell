/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talentum <talentum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 18:28:06 by ialvarez          #+#    #+#             */
/*   Updated: 2023/03/05 21:01:40 by talentum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigquit_handler(int sign)
{
	g_err_no = -1;
	(void)sign;
	ft_printf("exit\n");
	exit (0);
}

void	handle_signal(int sl)
{
	if (sl == 2)
	{
		g_err_no = -1;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
	}	
}

void	handle_signal_here(int sl)
{
	(void) sl;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
}

void	my_exit(char **argv, t_data *data)
{
	int	i;

	i = -1;
	if (argv[1])
	{
		if (!ft_strisdigit(argv[1]))
		{
			ft_printf("minishell: exit: %s: num argument required", argv[1]);
			exit(255);
		}
		g_err_no = ft_atoi(argv[1]);
		if (g_err_no < 0 || g_err_no == 1)
			g_err_no = 255;
	}
	else
	{
		if (data->env)
			g_err_no = ft_atoi(search_variable(data->env, "?="));
	}
	if (data->env && ft_atoi(search_variable(data->env, "SHLVL=")) > 1)
		write(1, "exit\n", 5);
	else
		write(1, "exit", 4);
	rl_clear_history();
	exit(g_err_no);
}

void	select_signal(int select)
{
	if (select == 0)
	{
		signal(SIGINT, handle_signal);
		if (signal(SIGQUIT, sigquit_handler) == SIG_ERR)
		{
			ft_printf("Error setting SIGQUIT handler\n");
			exit(1);
		}
	}
	else
	{
		signal(SIGINT, handle_signal_here);
		signal(SIGQUIT, SIG_IGN);
	}
}
