/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 21:10:00 by vifernan          #+#    #+#             */
/*   Updated: 2022/07/27 21:10:04 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipe	*create_node(char *cmd_stg)
{
	t_pipe	*ret;

	if (!cmd_stg)
		return (NULL);
	ret = malloc(sizeof(t_pipe));
	ft_bzero(ret, sizeof(t_pipe));
	ret->in_fd = take_heredoc(cmd_stg, -1);
	//take_redirections(ret, cmd_sp);
	//take_args_path(ret_cmd_sp);
	return (ret);
}

t_pipe	*tokenizator(t_data *data, int i)
{
	t_pipe	*ret;
	t_pipe	*new;

	if (!data->spt_pipes)
		return (NULL);
	while (data->spt_pipes[++i] != NULL)
	{
		if (i == 0)
		{
			ret = create_node(data->spt_pipes[i]);
			new = ret;
		}
		else
		{
			new->next = create_node(data->spt_pipes[i]);
			new = new->next;
		}
		free(data->spt_pipes[i]);
	}
	free(data->spt_pipes);
	return (ret);
}
