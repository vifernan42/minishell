/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:36:59 by ialvarez          #+#    #+#             */
/*   Updated: 2023/03/06 16:52:00 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ready_to_start(t_data *data, char *cmd_line)
{
	t_pipe	*pipe;

	data->spt_pipes = st_split(cmd_line, '|');
	if (data->spt_pipes[0] && even_quotes(cmd_line, 0, 0, data) == 0)
	{
		pipe = tokenizator(data, -1);
		if (data->err != -1 && pipe)
			exec_pipes(pipe, data);
		if (pipe)
			lstdelete(pipe);
	}
	if (data->spt_pipes)
		free_matrix(data->spt_pipes);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*cmd_line;
	int		i;

	cmd_line = start_variables(argc, argv, envp, &data);
	while (cmd_line)
	{
		i = 0;
		cmd_line = change_nbsp(start_variables(0, argv, data.env, &data));
		if (!cmd_line)
			ft_printf("exit\n");
		else
			while (cmd_line[i] == ' ')
				i++;
		if (cmd_line && g_err_no >= 0 && cmd_line[i] != '\0'
			&& (int)ft_strlen(cmd_line + i) > 0)
			ready_to_start(&data, cmd_line);
		free_variables(cmd_line, &data);
	}
}
