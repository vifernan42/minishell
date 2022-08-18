/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 21:10:00 by vifernan          #+#    #+#             */
/*   Updated: 2022/08/18 17:41:47 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipe	*create_node(char *cmd_stg, char *all_path)
{
	t_pipe	*ret;
	char	*aux_cmd;


	if (!cmd_stg)
		return (NULL);
	ret = (t_pipe *)malloc(sizeof(t_pipe));
	ft_bzero(ret, sizeof(t_pipe));
	aux_cmd = ft_strdup(cmd_stg);
	ft_printf("*rm_befo:	%s\n", aux_cmd);
	ret->in_fd = take_heredoc(&aux_cmd, -1, cmd_arg_quottes(cmd_stg), NULL);
	ft_printf("*rm-here:	%s\n", aux_cmd);
	if (aux_cmd)
		take_redirec(&aux_cmd, -1, cmd_arg_quottes(aux_cmd), ret);
	ft_printf("*rm_redr:	%s\n", aux_cmd);
	if (aux_cmd)
		take_args(cmd_arg_quottes(aux_cmd), ret, all_path);
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
			ret = create_node(data->spt_pipes[i], data->all_path);
			new = ret;
		}
		else
		{
			new->next = create_node(data->spt_pipes[i], data->all_path);
			new = new->next;
		}
	}
	return (ret);
}
