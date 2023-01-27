/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 18:28:06 by ialvarez          #+#    #+#             */
/*   Updated: 2023/01/26 20:06:09 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void sigquit_handler()
{
    printf("exit\n");
    exit(0);
}

void	handle_signal(int sl)
{
	if (sl == 2)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		//write(1, "\n", 1);
		rl_on_new_line();
		//rl_replace_line("", 0);
		//rl_redisplay();
		
		/*ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();*/
		
	}
	
}

void	handle_signal_here(int sl)
{
	(void) sl;
	err_no = 1;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
}

void		my_exit(t_data *data)
{
	if (ft_atoi(search_variable(data->env, "SHLVL=")) > 1)
	{
		write(1, "exit\n", 5);
		data->level--;
	}
	else
		write(1, "exit", 4);
	rl_clear_history();
	exit(0);
}

void	select_signal(int select){
	if (select == 0)
	{
		signal(SIGINT, handle_signal);
		if (signal(SIGQUIT, sigquit_handler) == SIG_ERR)
		{
			printf("Error setting SIGQUIT handler\n");
			exit(1);
		}
	}
	else
	{
		signal(SIGINT, handle_signal_here);
		signal(SIGQUIT, SIG_IGN);
	}
}