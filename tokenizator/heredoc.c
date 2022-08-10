/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 21:09:27 by vifernan          #+#    #+#             */
/*   Updated: 2022/08/09 18:08:22 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rdline_heredoc(char *key, int fd_w)
{
	char	*wr_on;

	if (!key)
		return ;
	wr_on = NULL;
	while (1)
	{
		wr_on = readline("> ");
		if (ft_strcmp(key, wr_on) == 0)
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
	return (pip[RD_END]);
}

int	take_heredoc(char **aux_cmd, int i, char **cmd_sp, char *aux)
{
	char	*key;
	int		fd;
	int		join;

	fd = 0;
	join = 0;
	i = find_heredoc(cmd_sp, -1, 1);
	key = NULL;
	if (i != -1)
	{
		if ((int)ft_strlen(cmd_sp[i]) > 2)
		{
			key = ft_strdup(ft_strchr2(cmd_sp[i], '<')); /*modificar*/
			join++;
		}
		else
			key = ft_strdup(cmd_sp[i + 1]);
		aux = rm_heredoc(cmd_sp, i, join);  /*rm modificar  >>ho"la>a" c archivo hola>a */
		free(*aux_cmd);
		*aux_cmd = ft_strdup(aux);
		free(aux);
		fd = do_heredoc(skip_quotes(key));
		if (key)
			free(key);
	}
	else
	{
		free_matrix(cmd_sp);
		return (0);
	}
	if (find_heredoc(cmd_arg_quottes(*aux_cmd), 0, 1) == -1)
	{
		write(1, "\n", 1);
		free_matrix(cmd_sp);
		return (fd);
	}
	free_matrix(cmd_sp);
	return (take_heredoc(aux_cmd, -1, cmd_arg_quottes(*aux_cmd), NULL));
}
