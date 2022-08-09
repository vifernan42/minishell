/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:08:38 by vifernan          #+#    #+#             */
/*   Updated: 2022/08/09 17:03:39 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*take_fname(char **cmd_sp, int i, int x, int *join)
{
	char	*fname;
	char	*aux;
	int		o;
	int		flag;
	
	flag = -1;
	o = -1;
	fname = NULL;
	aux = NULL;
	//printf ("")
	if ((int)ft_strlen(cmd_sp[i]) > x) /* >a>b return: a */
	{
		if (ft_strnstr(cmd_sp[i], ">>", 2) && x == 2)
		{
			aux = ft_strchr(cmd_sp[i], '>') + 2; /*me da a mi que esto no*/
			while (aux[++o] != '\0')
				if (aux[o] == '>' || aux[o] == '<')
					break ;
			fname = ft_substr(aux, 0, ft_strlen(aux) - (ft_strlen(aux) - o));
			printf("----  %s\n", cmd_sp[i]);	
		}
		else if(ft_str2chr(cmd_sp[i], '>') && x == 1)
		{
			o = -1;
			aux = ft_strchr(cmd_sp[i], '>') + 1;
			while (aux[++o] != '\0')
				if (aux[o] == '>' || aux[o] == '<')
					break ;
			fname = ft_substr(aux, 0, ft_strlen(aux) - (ft_strlen(aux) - o));
			printf("----  %s\n", cmd_sp[i]);
		}
		else
			fname = ft_substr(cmd_sp[i], 1, ft_strlen(cmd_sp[i]) - 1);
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
		if (ft_strnstr(cmd_sp[i], "<<", 2) || ft_strnstr(cmd_sp[i], ">>", 2))
			fname = take_fname(cmd_sp, i, 2, &join);
		else
			fname = take_fname(cmd_sp, i, 1, &join);
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