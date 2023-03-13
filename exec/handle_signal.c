/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:37:55 by vifernan          #+#    #+#             */
/*   Updated: 2023/03/13 17:22:12 by ialvarez         ###   ########.fr       */
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
