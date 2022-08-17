/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:08:38 by vifernan          #+#    #+#             */
/*   Updated: 2022/08/17 16:13:33 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_redirec(char	*id, char *fname, t_pipe *ret)
{
	int	fd;
	int	found;

	found = find_rm_size(id, 0, &found, -1);
	if (ft_strnstr((char *)id + found, "<", 1))
	{
		fd = open(fname, O_RDONLY, 0666);
		if (ret->in_fd)
			close(ret->in_fd);
		ret->in_fd = fd;
	}
	else if (ft_strnstr((char *)id + found, ">", 1)
				|| ft_strnstr((char *)id + found, ">>", 2))
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
	int		j;

	fname = NULL;
	j = 0;
	i = find_heredoc(cmd_sp, -1, -1);
	if (i != -1)
	{
		if ((ft_strnstr(cmd_sp[i], ">>", 2) && (int)ft_strlen(cmd_sp[i]) == 2)
				|| (ft_strnstr(cmd_sp[i], ">", 1) && (int)ft_strlen(cmd_sp[i]) == 1))
			fname = find_key(cmd_sp[i + 1], -1, 0);
		else if (ft_strnstr(cmd_sp[i], ">>", 2) && (int)ft_strlen(cmd_sp[i]) > 2)
			fname = find_key(ft_strchr2(cmd_sp[i], '>'), -1, 0);
		else if (ft_strnstr(cmd_sp[i], ">", 1) && (int)ft_strlen(cmd_sp[i]) > 1)
			fname = find_key(ft_strchr(cmd_sp[i], '>') + 1, -1, 0);
		else if ((ft_strnstr(cmd_sp[i], "<", 1) && (int)ft_strlen(cmd_sp[i]) == 1))
			fname = find_key(cmd_sp[i + 1], -1, 0);
		else if (ft_strnstr(cmd_sp[i], "<", 1) && (int)ft_strlen(cmd_sp[i]) > 1)
			fname = find_key(ft_strchr(cmd_sp[i], '<') + 1, -1, 0);
		else
		{
			fname = find_key((char *) cmd_sp[i] + find_rm_size(cmd_sp[i], 0, &j, -1) + 1, -1, 0);
			if (fname[0] == '\0')
				fname = find_key((char *) cmd_sp[i] + find_rm_size(cmd_sp[i], 0, &j, -1) + 2, -1, 0);
		}
		do_redirec(cmd_sp[i], skip_quotes(fname), ret);
		free(fname);
		//printf("-----------------------\n");
		fname = rm_heredoc(cmd_sp, i, -1, 0);
		//printf("rm_redir:	%s\n", fname);
		free(*aux_cmd);
		*aux_cmd = ft_strdup(fname);
		free(fname);
	}
	if (find_heredoc(cmd_arg_quottes(*aux_cmd), 0, 1) == -1)
	{
		free_matrix(cmd_sp);
		return ;
	}
	free_matrix(cmd_sp);
	take_redirec(aux_cmd, -1, cmd_arg_quottes(*aux_cmd), ret);
}