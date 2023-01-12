/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 21:10:00 by vifernan          #+#    #+#             */
/*   Updated: 2023/01/12 19:28:48 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipe	*create_node(char *cmd_stg, char *all_path, t_data *data)
{
	t_pipe	*ret;
	char	*aux_cmd;

	if (!cmd_stg)
		return (NULL);
	ret = (t_pipe *)malloc(sizeof(t_pipe));
	ft_bzero(ret, sizeof(t_pipe));
	ret->out_fd = 1;
	ret->in_fd = 0;
	aux_cmd = ft_strdup(cmd_stg);
	ret->in_fd = take_heredoc(&aux_cmd, cmd_arg_quottes(cmd_stg, data), NULL, data);
	if (aux_cmd)
		take_redirec(&aux_cmd, cmd_arg_quottes(aux_cmd, data), ret, data);
	if (aux_cmd)
		take_args(cmd_arg_quottes(aux_cmd, data), ret, all_path);
	free(aux_cmd);
	if (ret->in_fd == -1)
	{
		printf("minishell: Bad file fd\n");
		data->err = -1;
	}
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
			ret = create_node(data->spt_pipes[i], data->all_path, data);
			new = ret;
		}
		else
		{
			new->next = create_node(data->spt_pipes[i], data->all_path, data);
			new = new->next;
		}
	}
	return (ret);
}
