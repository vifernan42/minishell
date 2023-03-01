/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liberator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:55:38 by vifernan          #+#    #+#             */
/*   Updated: 2023/02/28 20:57:54 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	nodedelete(t_pipe *pipe, t_pipe **next)
{
	if (pipe->exec_path)
		free(pipe->exec_path);
	if (pipe->argv)
		free_matrix(pipe->argv);
	*next = pipe->next;
	free(pipe);
}

void	lstdelete(t_pipe *pipe)
{
	t_pipe	*next;

	if (!pipe)
		return ;
	next = NULL;
	while (pipe)
	{
		nodedelete(pipe, &next);
		pipe = next;
	}
}

void	free_variables(char	*cmd_line, t_data *data)
{
	char	*join;

	add_history(cmd_line);
	if (cmd_line)
		free(cmd_line);
	if (data->promt)
		free(data->promt);
	if (data->all_path)
		free(data->all_path);
	if (g_err_no == 256 || g_err_no == 13 || g_err_no == -1)
		g_err_no = 1;
	join = ft_itoa(g_err_no);
	if (data->env)
		env_update(data, ft_strjoin("?=", join), "?=");
	free(join);
}
