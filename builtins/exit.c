/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 18:28:06 by ialvarez          #+#    #+#             */
/*   Updated: 2022/12/26 18:35:39 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void sigquit_handler()
{
    printf("Exit\n");
    exit(0);
}

void	handle_signal(int sl)
{

	printf("%d\n", sl);
	if (sl == 2)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	
}

void		my_exit()
{
	write(1, "exit\n", 5);
	rl_clear_history();
	exit(0);
}
