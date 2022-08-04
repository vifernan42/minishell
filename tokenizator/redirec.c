/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:08:38 by vifernan          #+#    #+#             */
/*   Updated: 2022/08/04 15:52:47 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*take_fname(char **cmd_sp, int i, int x, int *join)
{
	char	*fname;
	int		flag;
	
	flag = -1;
	if ((int)ft_strlen(cmd_sp[i]) > x)
	{
		fname = ft_substr(cmd_sp[i], x, ft_strlen(cmd_sp[i]) - x);
		*join = 1;
	}
	else
		fname = ft_strdup(cmd_sp[i + 1]);
	return (fname);
}

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
	int		join;

	fname = NULL;
	join = 0;
	i = find_heredoc(cmd_sp, -1, 2);
	if (i != -1)
	{
		if (ft_strnstr(cmd_sp[i], "<", 1))
			fname = take_fname(cmd_sp, i, 1, &join);
		else
			fname = take_fname(cmd_sp, i, 2, &join);
		do_redirec(cmd_sp[i], skip_quotes(fname), ret);
		free(fname);
		fname = rm_heredoc(cmd_sp, i, join);
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