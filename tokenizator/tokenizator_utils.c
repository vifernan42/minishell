/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizator_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 12:47:53 by vifernan          #+#    #+#             */
/*   Updated: 2023/02/15 21:27:49 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cmd_arg_quottes(char	*pipe, t_data *data)
{
	char	**aux_cmd;
	char	*aux;
	int		x;
	int		i;

	data->err = 0;
	aux = NULL;
	if (!pipe)
		return (NULL);
	aux_cmd = spqu_split(skip_spaces(pipe), ' ');
	x = -1;
	i = 0;
	while (aux_cmd[++x] != NULL)
	{
		if (!ft_strcmp_built(aux_cmd[x], "echo"))
			i++;
		if (find_rm_size(aux_cmd[x], 0, -1) == (int)ft_strlen(aux_cmd[x])
			&& i == 0)
			aux = skip_quotes(skip_spaces(aux_cmd[x]), 0);
		else
			aux = skip_spaces(aux_cmd[x]);
		free(aux_cmd[x]);
		aux_cmd[x] = aux;
	}
	return (aux_cmd);
}

static int	aux_find_her(int type, char **cmd_sp, int i)
{
	if ((type == 0 && ft_strnstr(cmd_sp[i], "<<", 2))
		|| (type != 0 && (ft_strnstr(cmd_sp[i], "<", 1)
				|| ft_strnstr(cmd_sp[i], ">>", 2)
				|| ft_strnstr(cmd_sp[i], ">", 1)))
		|| find_rm_size(cmd_sp[i], 0, type) != (int)ft_strlen(cmd_sp[i]))
		return (0);
	if (type == (int)ft_strlen(cmd_sp[i]) || (cmd_sp[i][type] != '<'
		|| cmd_sp[i][type + 1] != '<'))
		return (1);
	return (4);
}

static void	check_flag(int *i, int *flag)
{
	if (*i == 0)
	{
		*flag = 1;
		(*i)--;
	}
}

int	find_heredir(char **cmd_sp, int i, int type)
{
	int		flag;

	if (!cmd_sp)
		return (-1);
	flag = 0;
	check_flag(&i, &flag);
	while (cmd_sp[++i] != NULL)
		if (aux_find_her(type, cmd_sp, i) == 0)
			break ;
	if (cmd_sp[i] == NULL)
	{
		if (flag > 0)
			free_matrix(cmd_sp);
		return (-1);
	}
	if (type == 0)
	{
		type = find_rm_size(cmd_sp[i], 0, type);
		if (aux_find_her(type, cmd_sp, i) == 1)
			return (-1);
	}
	if (flag > 0)
		free_matrix(cmd_sp);
	return (i);
}

int	find_rm_size(char *str, int lock, int type)
{
	char	c;
	int		i;

	i = -1;
	c = '\0';
	if (!str)
		return (0);
	while (str[++i] != '\0')
	{
		if (lock % 2 == 0 && (((type == 0 || type == 5)
					&& str[i] == '<' && str[i + 1] == '<')
				|| (type != 0 && (str[i] == '<' || str[i] == '>'))))
			break ;
		if ((str[i] == '\'' || str[i] == '\"') && (c == '\0' && lock % 2 == 0))
		{
			if (str[i] == '\'')
				c = '\'';
			else
				c = '\"';
			lock += 1;
		}
		else if ((c == '\'' || c == '\"') && str[i] == c && lock++)
			c = '\0';
	}
	return (i);
}
