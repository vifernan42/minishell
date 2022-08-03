/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 21:10:00 by vifernan          #+#    #+#             */
/*   Updated: 2022/08/03 17:05:01 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipe	*create_node(char *cmd_stg)
{
	t_pipe	*ret;
	char	*aux_cmd;


	if (!cmd_stg)
		return (NULL);
	ret = (t_pipe *)malloc(sizeof(t_pipe));
	ft_bzero(ret, sizeof(t_pipe));
	aux_cmd = ft_strdup(cmd_stg);
	ret->in_fd = take_heredoc(&aux_cmd, -1, cmd_arg_quottes(cmd_stg), NULL);
	ft_printf("DES: %d\n", ret->in_fd);
	take_redirec(&aux_cmd, -1, cmd_arg_quottes(aux_cmd));
	free(aux_cmd);
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
