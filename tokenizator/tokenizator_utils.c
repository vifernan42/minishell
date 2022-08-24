/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizator_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 12:47:53 by vifernan          #+#    #+#             */
/*   Updated: 2022/08/23 18:28:28 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ret_key(char *str, int i, int j, char c)
{
	int		lock;
	char	*ret;

	lock = 0;
	ret = malloc(sizeof(char) * j + 1);
	j = 0;
	while (str[++i] != '\0')
	{
		if ((str[i] == '<' || str[i] == '>') && lock == 0)
			break ;
		if ((str[i] == '\'' || str[i] == '\"') && (c == 0 && lock == 0))
		{
			if (str[i] == '\'')
				c = '\'';
			else
				c = '\"';
			lock = 1;
		}
		else if ((c == '\'' || c == '\"') && str[i] == c && lock == 1)
		{
			c = 0;
			lock = 0;
		}
		else if ((str[i] != '\'' && str[i] != '\"') || lock == 1)
			ret[j++] = str[i];
	}
	ret[j] = '\0';
	return (ret);
}

char	*find_key(char *str, int i, int j)
{
	char	c;
	int		lock;

	c = '\0';
	lock = 0;
	while (str[++i] != '\0')
	{
		if ((str[i] == '<' || str[i] == '>') && lock == 0)
			break ;
		if ((str[i] == '\'' || str[i] == '\"') && (c == 0 && lock == 0))
		{
			if (str[i] == '\'')
				c = '\'';
			else
				c = '\"';
			lock = 1;
		}
		else if ((c == '\'' || c == '\"') && str[i] == c && lock == 1)
		{
			c = 0;
			lock = 0;
		}
		else if ((str[i] != '\'' && str[i] != '\"') || lock == 1)
			j++;
	}
	return (ret_key(str, -1, j, '\0'));
}

char	**cmd_arg_quottes(char	*pipe)
{
	char	**aux_cmd;
	char	*aux;
	int		x;
	int		j;

	aux = NULL;
	j = 0;
	if (!pipe)
		return (NULL);
	aux_cmd = spqu_split(skip_spaces(pipe), ' ');
	x = -1;
	while (aux_cmd[++x] != NULL)
	{
		if (aux_cmd[x][0] != '$' && find_rm_size(aux_cmd[x], 0, 0, -1) == (int)ft_strlen(aux_cmd[x]))
			aux = skip_quotes(skip_spaces(aux_cmd[x]));
		else
			aux = skip_spaces(aux_cmd[x]);
		free(aux_cmd[x]);
		aux_cmd[x] = aux;
	}
	return (aux_cmd);
}

int	find_heredir(char **cmd_sp, int i, int type)
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
		if ((type == 0 && ft_strnstr(cmd_sp[i], "<<", 2)) || (type != 0 && (ft_strnstr(cmd_sp[i], "<", 1)
			|| ft_strnstr(cmd_sp[i], ">>", 2) || ft_strnstr(cmd_sp[i], ">", 1))) 
			|| find_rm_size(cmd_sp[i], 0, 0, type) != (int)ft_strlen(cmd_sp[i]))
				break ;
	if (cmd_sp[i] == NULL)
	{
		if (flag > 0)
			free_matrix(cmd_sp);
		return (-1);
	}
	if (type == 0)
	{
		type = find_rm_size(cmd_sp[i], 0, 0, type);
		if (type == (int)ft_strlen(cmd_sp[i]) || (cmd_sp[i][type] != '<' || cmd_sp[i][type + 1] != '<'))
			return (-1);
	}
	if (flag > 0)
			free_matrix(cmd_sp);
	return (i);
}

int		find_rm_size(char *str, int i, int lock, int type)
{
	char	c;

	c = '\0';
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (lock % 2 == 0 && (((type == 0 || type == 5)
				&& str[i] == '<' && str[i + 1] == '<')
				|| ( type != 0 && (str[i] == '<' || str[i] == '>'))))
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
		i++;
	}
	return (i);
}