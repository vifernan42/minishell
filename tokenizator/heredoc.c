/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 21:09:27 by vifernan          #+#    #+#             */
/*   Updated: 2023/01/11 18:47:59 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rdline_heredoc(char *key, int fd_w)
{
	char	*wr_on;

	if (!key)
		return ;
	wr_on = NULL;
	select_signal(1);
	while (1)
	{
		wr_on = readline("> ");
		if (err_no == 1 || ft_strcmp(key, wr_on) == 0 || wr_on == NULL)
			break ;
		write(fd_w, wr_on, ft_strlen(wr_on));
		write(fd_w, "\n", 1);
		free(wr_on);
	}
	if (wr_on)
		free(wr_on);
}

static int	do_heredoc(char *key)
{
	int	pip[2];

	if (pipe(pip) < 0)
		return (0);
	rdline_heredoc(key, pip[WR_END]);
	close(pip[WR_END]);
	if (key)
		free(key);
	if (err_no == 1)
	{
		close(pip[WR_END]);
		close(pip[RD_END]);
		if (pipe(pip) < 0)
			return (0);
		close(pip[WR_END]);
	}
	return (pip[RD_END]);
}

char	*key_value(char **cmd_sp, int i)
{
	char	*key;

	if ((int)ft_strlen(cmd_sp[i]) > 2)
		key = find_key((char *) cmd_sp[i] + find_rm_size(cmd_sp[i], 0, 0, 0)
				+ 2, -1, 0);
	else
		key = find_key(cmd_sp[i + 1], -1, 0);
	return (key);
}

int	take_heredoc(char **aux_cmd, int i, char **cmd_sp, char *aux)
{
	int		fd;

	fd = 0;
	i = find_heredir(cmd_sp, -1, 0);
	if (i != -1)
	{
		fd = do_heredoc(skip_quotes(key_value(cmd_sp, i), -1));
		aux = rm_used(cmd_sp, i, 0, 2);
		free(*aux_cmd);
		*aux_cmd = ft_strdup(aux);
		free(aux);
	}
	else
	{
		free_matrix(cmd_sp);
		return (0);
	}
	if (find_heredir(cmd_arg_quottes(*aux_cmd), 0, 0) == -1)
	{
		free_matrix(cmd_sp);
		return (fd);
	}
	free_matrix(cmd_sp);
	return (take_heredoc(aux_cmd, -1, cmd_arg_quottes(*aux_cmd), NULL));
}
