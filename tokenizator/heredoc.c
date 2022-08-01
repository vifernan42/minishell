/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 21:09:27 by vifernan          #+#    #+#             */
/*   Updated: 2022/08/01 17:39:24 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_heredoc(char **cmd_sp, int i)
{
	if (!cmd_sp)
		return (-1);
	while (cmd_sp[++i] != NULL)
	{
		if (ft_strnstr(cmd_sp[i], "<<<", 3))
			printf("Error");
		if (ft_strnstr(cmd_sp[i], "<<", 2))
			break ;
	}
	if (cmd_sp[i] == NULL)
		return (-1);
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
	//free_matrix(cmd_sp); /*no hay que liberar aqui en principio*/
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
	write(STDERR_FILENO, "AH\n", 3);
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

int	take_heredoc(char **cmd_stg, int i, char **cmd_sp, char *aux)
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
		//free(*cmd_stg);                     /*lo quite porque al parecer hace double free*/
		//printf("***%s\n", *cmd_stg);
		//printf("%s | %p\n", *cmd_stg);
		*cmd_stg = aux;
		fd = do_heredoc(key);
		write(STDERR_FILENO, "EH\n", 3);
		free(key);
	}
	if (find_heredoc(cmd_arg_quottes(*cmd_stg), -1) == -1)
	{
		free_matrix(cmd_sp); /*necesario*/
		write(1, "EXIT\n", 5);
		return (fd);
	}
	free_matrix(cmd_sp);   /*necesario*/
	return (take_heredoc(cmd_stg, -1, cmd_arg_quottes(*cmd_stg), NULL));
	/*free_matrix(cmd_sp);*/
	//return (0);
}
