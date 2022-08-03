/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 21:09:27 by vifernan          #+#    #+#             */
/*   Updated: 2022/08/03 13:46:29 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_heredoc(char **cmd_sp, int i)
{
	int		flag;

	if (!cmd_sp)
		return (-1);
	flag = 0;
	if (i == 0)
	{
		i = -1;
		flag = 1;
	}
	while (cmd_sp[++i] != NULL)
		if (ft_strnstr(cmd_sp[i], "<<", 2))
			break ;
	if (cmd_sp[i] == NULL)
	{
		if (flag > 0)
			free_matrix(cmd_sp);
		return (-1);
	}
	if (flag > 0)
			free_matrix(cmd_sp);
	return (i);
}

char	*ft_strjoin_swap(char	*str, char	*str2)
{
	char	*aux;

	aux = ft_strdup(str);
	free(str);
	str = ft_strjoin(aux, str2);
	free (aux);
	return (str);
}

char	*rm_heredoc(char **cmd_sp, int i, int join)
{
	char	*aux;
	char	*ret;
	int		x;

	x = -1;
	ret = NULL;
	aux = NULL;
	while (cmd_sp[++x] != NULL)
	{
		if ((join == 1 && x != i) || (join == 0 && x != i && x -1 != i))
		{
			if (!ret)
				ret = ft_strdup(cmd_sp[x]);
			else
				ret = ft_strjoin_swap(ret, cmd_sp[x]);
			ret = ft_strjoin_swap(ret, " ");
		}
	}
	return (ret);
}

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
	i = find_heredoc(cmd_sp, -1);
	key = NULL;
	if (i != -1)
	{
		if ((int)ft_strlen(cmd_sp[i]) > 2)
		{
			key = ft_substr(cmd_sp[i], 2, ft_strlen(cmd_sp[i]) - 2);
			join++;
		}
		else
			key = ft_strdup(cmd_sp[i + 1]);
		aux = rm_heredoc(cmd_sp, i, join);
		free(*aux_cmd);
		*aux_cmd = ft_strdup(aux);
		free(aux);
		fd = do_heredoc(key);
		free(key);
	}
	else
		return (0);
	if (find_heredoc(cmd_arg_quottes(*aux_cmd), 0) == -1)
	{
		free_matrix(cmd_sp);
		return (fd);
	}
	free_matrix(cmd_sp);
	return (take_heredoc(aux_cmd, -1, cmd_arg_quottes(*aux_cmd), NULL));
}
