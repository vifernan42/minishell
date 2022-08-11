/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:08:38 by vifernan          #+#    #+#             */
/*   Updated: 2022/08/11 18:58:31 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_redirec(char	*id, char *fname, t_pipe *ret)
{
	int	fd;

	if (ft_strnstr(id, "<", 1))
	{
		fd = open(fname, O_RDONLY, 0666);
		if (ret->in_fd)
			close(ret->in_fd);
		ret->in_fd = fd;
	}
	else if (ft_strnstr(id, ">", 1) || ft_strnstr(id, ">>", 2))
	{
		if (ft_strnstr(id, ">>", 2))
			fd = open(fname, O_WRONLY | O_CREAT | O_APPEND, 0666);
		else
			fd = open(fname, O_WRONLY | O_CREAT | O_CREAT, 0666);
		if (ret->out_fd)
			close(ret->out_fd);
		ret->out_fd = fd;
	}
}

void 	take_redirec(char **aux_cmd, int i, char **cmd_sp, t_pipe *ret)
{
	char	*fname;

	fname = NULL;
	i = find_heredoc(cmd_sp, -1, 2);
	if (i != -1)
	{
		if ((ft_strnstr(cmd_sp[i], ">>", 2) && (int)ft_strlen(cmd_sp[i]) == 2)
				|| (ft_strnstr(cmd_sp[i], ">", 1) && (int)ft_strlen(cmd_sp[i]) == 1))
			fname = find_key(cmd_sp[i + 1], -1, 0);
		else if (ft_strnstr(cmd_sp[i], ">>", 2) && (int)ft_strlen(cmd_sp[i]) > 2)
			fname = find_key(ft_strchr2(cmd_sp[i], '>'), -1, 0);
		else if (ft_strnstr(cmd_sp[i], ">", 1) && (int)ft_strlen(cmd_sp[i]) > 1)
			fname = find_key(ft_strchr(cmd_sp[i], '>') + 1, -1, 0);
		do_redirec(cmd_sp[i], skip_quotes(fname), ret);
		free(fname);
		fname = rm_heredoc(cmd_sp, i, 0);
		free(*aux_cmd);
		*aux_cmd = ft_strdup(fname);
		free(fname);
	}
	if (find_heredoc(cmd_arg_quottes(*aux_cmd), 0, 2) == -1)
	{
		free_matrix(cmd_sp);
		return ;
	}
	free_matrix(cmd_sp);
	take_redirec(aux_cmd, -1, cmd_arg_quottes(*aux_cmd), ret);
}