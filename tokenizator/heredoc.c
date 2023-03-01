/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 21:09:27 by vifernan          #+#    #+#             */
/*   Updated: 2023/03/01 19:29:52 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	rdline_heredoc(t_data *data, char *key, int fd_w)
{
	char	*wr_on;

	if (!key)
		return ;
	wr_on = NULL;
	data->err = data->err;
	select_signal(1);
	while (1)
	{
		signal(SIGINT, handle_signal_here);
		wr_on = readline("> ");
		if (g_err_no == 1 || (!ft_strcmp(key, wr_on)
				&& (int)ft_strlen(key) == (int)ft_strlen(wr_on))
			|| wr_on == NULL)
			break ;
		wr_on = take_variable(data, wr_on);
		write(fd_w, wr_on, ft_strlen(wr_on));
		write(fd_w, "\n", 1);
		free(wr_on);
	}
	if (wr_on)
		free(wr_on);
}

static int	do_heredoc(t_data *data, char *key)
{
	int	pip[2];

	if (pipe(pip) < 0)
		return (0);
	rdline_heredoc(data, key, pip[WR_END]);
	close(pip[WR_END]);
	if (key)
		free(key);
	if (g_err_no == 1)
	{
		close(pip[WR_END]);
		close(pip[RD_END]);
		if (pipe(pip) < 0)
			return (0);
		close(pip[WR_END]);
	}
	return (pip[RD_END]);
}

static char	*key_value(char **cmd_sp, int i)
{
	char	*key;

	if ((int)ft_strlen(cmd_sp[i]) > 2)
		key = find_key((char *) cmd_sp[i] + find_rm_size(cmd_sp[i], 0, 0)
				+ 2, -1, 0);
	else
		key = find_key(cmd_sp[i + 1], -1, 0);
	return (key);
}

static	int	aux_take(char **aux_cmd, char **cmd_sp, int *fd, t_data *data)
{
	int		i;
	char	*aux;

	i = find_heredir(cmd_sp, -1, 0);
	if (i != -1)
	{
		*fd = do_heredoc(data, skip_quotes(key_value(cmd_sp, i), 0));
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
	return (1);
}

int	take_heredoc(char **aux_cmd, char **cmd_sp, char *aux, t_data *data)
{
	int		fd;
	int		i;

	fd = 0;
	i = 1;
	i = aux_take(aux_cmd, cmd_sp, &fd, data);
	aux = NULL;
	if (i == 0)
		return (0);
	if (find_heredir(cmd_arg_quottes(*aux_cmd, data), 0, 0) == -1)
	{
		free_matrix(cmd_sp);
		return (fd);
	}
	close(fd);
	free_matrix(cmd_sp);
	return (take_heredoc(aux_cmd, cmd_arg_quottes(*aux_cmd, data), NULL, data));
}
