/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 18:28:06 by ialvarez          #+#    #+#             */
/*   Updated: 2023/03/13 16:26:27 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_args(char **argv)
{
	if (!ft_strisdigit(argv[1]))
	{
		ft_printf("minishell: exit: %s: num argument required", argv[1]);
		rl_clear_history();
		exit(255);
	}
	if (argv[2] != NULL)
	{
		ft_printf("exit\n");
		ft_printf("minishell: exit: too many arguments\n");
		g_err_no = 1;
		return (0);
	}
	g_err_no = ft_atoi(argv[1]);
	if (g_err_no < 0 || g_err_no == 1)
		g_err_no = 255;
	return (1);
}

void	my_exit(char **argv, t_data *data)
{
	int	i;

	i = -1;
	if (argv[1])
	{
		if (!exit_args(argv))
			return ;
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
