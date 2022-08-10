/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizator_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 12:47:53 by vifernan          #+#    #+#             */
/*   Updated: 2022/08/10 16:19:08 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cmd_arg_quottes(char	*pipe)
{
	char	**aux_cmd;
	char	*aux;
	int		x;

	aux = NULL;
	if (!pipe)
		return (NULL);
	aux_cmd = spqu_split(skip_spaces(pipe), ' ');
	x = -1;
	while (aux_cmd[++x] != NULL)
	{
		if (aux_cmd[x][0] != '$' && aux_cmd[x][0] != '<' && aux_cmd[x][0] != '>')
		{
			aux = skip_quotes(skip_spaces(aux_cmd[x]));
		}
		else
			aux = skip_spaces(aux_cmd[x]);
		free(aux_cmd[x]);
		aux_cmd[x] = aux;
	}
	return (aux_cmd);
}

int	find_heredoc(char **cmd_sp, int i, int x)
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
	{
		if ((ft_strnstr(cmd_sp[i], "<<", ft_strlen(cmd_sp[i])) && x == 1) || (x == 2 &&
		(ft_strnstr(cmd_sp[i], "<", ft_strlen(cmd_sp[i])) ||
		ft_strnstr(cmd_sp[i], ">", ft_strlen(cmd_sp[i])) ||
		ft_strnstr(cmd_sp[i], ">>", ft_strlen(cmd_sp[i])))))
			break ;
	}
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

char	*ft_strjoin_swap(char	*ret, char	*str)
{
	char	*aux;

	if (!ret)
		return (ft_strdup(ret));
	else
	{
		aux = ft_strdup(ret);
		free(ret);
		ret = ft_strjoin(aux, str);
		free (aux);
	}
	return (ret);
}
/*
char	*rm_heredoc(char **cmd_sp, int i, int join)
{
	char	*ret;
	int		x;
	int		flag;

	cat >>hola >gola >ljeknr
	
	x = -1;
	ret = NULL;
	flag = 0;
	if (ft_strnstr(cmd_sp[i], ">>", 2) || ft_strnstr(cmd_sp[i], "<<", 2))
		flag++;
	while (cmd_sp[++x] != NULL)
	{
		if (join % 2 != 0 &&  && x != i)
			ret = ft_strjoin_swap(ret, cmd_sp[x]);
		else if ()
	}
}
*/



char	*rm_heredoc(char **cmd_sp, int i, int join)
{
	char	*ret;
	int		x;

	x = -1;
	ret = NULL;
	while (cmd_sp[++x] != NULL)
	{
		if (join == 1 && ft_str2chr(cmd_sp[x], '>') && x == i)
		{
			if (!ret)
			{
				
				ret  = ft_strdup(ft_str2chr(cmd_sp[x], '>'));
			}
			else
				ret = ft_strjoin_swap(ret, ft_str2chr(cmd_sp[x], '>'));
			printf("ret2:	%s\n", ret);
		}
		else if (join == 1 && x == i && (cmd_sp[x][0] != '<' && cmd_sp[x][0] != '>'))
		{
			if (!ret)
				ret  = ft_strinit(cmd_sp[x], '<');
			else
				ret = ft_strjoin_swap(ret, ft_strinit(cmd_sp[x], '<'));
			printf("ret3:	%s\n", ret);
		}
		else if ((join == 1 && x != i) || (join == 0 && x != i && x - 1 != i))
		{
			if (!ret)
			{
				ret = ft_strdup(cmd_sp[x]);
				printf("---%s$\n", ret);
			}
			else
			{
				ret = ft_strjoin_swap(ret, cmd_sp[x]);
				ret = skip_redir(ret, &x);
				printf("ret4:	%s$\n", ret);
			}
		}
		ret = ft_strjoin_swap(ret, " ");
		printf("ret:	%s$\n", ret);
		
	}
	//printf("=	%s$\n", ret);
	return (ret);
}