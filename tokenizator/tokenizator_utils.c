/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizator_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 12:47:53 by vifernan          #+#    #+#             */
/*   Updated: 2022/08/04 13:00:51 by vifernan         ###   ########.fr       */
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
		if ((ft_strnstr(cmd_sp[i], "<<", 2) && x == 1) || (x == 2 &&
		(ft_strnstr(cmd_sp[i], "<", 1) ||
		ft_strnstr(cmd_sp[i], ">", 1) ||
		ft_strnstr(cmd_sp[i], ">>", 2))))
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