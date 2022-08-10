/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizator_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 12:47:53 by vifernan          #+#    #+#             */
/*   Updated: 2022/08/10 18:26:55 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ret_key(char *str, int i, int j, char c)
{
	char	lock;
	char	*ret;

	lock = 0;
	ret = malloc(sizeof(char) * j + 1);
	j = 0;
	while (str[++i] != '\0')
	{
		if ((str[i] == '<' || str[i] == '>') && lock == 0)
			break ;
		if ((str[i] == '\'' || str[i] == '\"') && lock == 0)
		{
			if (str[i] == '\'')
				c = '\'';
			else
				c = '\"';
			lock++;
			i++;
		}
		else if ((c == '\'' || c == '\"') && str[i] == c)
			lock--;
		if ((str[i] != '\'' && str[i] != '\"') || lock == 1)
			ret[j++] = str[i];
	}
	ret[j] = '\0';
	return (ret);
}

char	*find_key(char *str, int i, int j)
{
	char	c;
	char	lock;

	c = '\0';
	lock = 0;
	printf("<	%s\n", str);
	while (str[++i] != '\0')
	{
		if ((str[i] == '<' || str[i] == '>') && lock % 2 == 0)
			break ;
		if ((str[i] == '\'' || str[i] == '\"') && (c == '\0' && lock % 2 == 0))
		{
			if (str[i] == '\'')
				c = '\'';
			else
				c = '\"';
			lock++;
		}
		else if ((c == '\'' || c == '\"') && str[i] == c)
			lock++;
		if ((str[i] != '\'' && str[i] != '\"') || lock % 2 != 0)
			j++;
	}
	return (ret_key(str, -1, j, '\0'));
}


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
		if (aux_cmd[x][0] != '$' && aux_cmd[x][0] != '<' && aux_cmd[x][0] != '>'
				&& aux_cmd[x - 1][0] != '<' && aux_cmd[x - 1][0] != '>')
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
		return (ft_strdup(str));
	else
	{
		aux = ft_strdup(ret);
		free(ret);
		ret = ft_strjoin(aux, str);
		free (aux);
	}
	return (ret);
}

int		find_rm_size(char *str, int i, int j, int *lock)
{
	char	c;

	c = '\0';
	while (str[++i] != '\0')
	{
		if ((str[i] == '<' || str[i] == '>') && *lock % 2 == 0)
			break ;
		if ((str[i] == '\'' || str[i] == '\"') && (c == '\0' && *lock % 2 == 0))
		{
			if (str[i] == '\'')
				c = '\'';
			else
				c = '\"';
			*lock += 1;
		}
		else if ((c == '\'' || c == '\"') && str[i] == c)
			*lock += 1;
		if ((str[i] != '\'' && str[i] != '\"') || *lock % 2 != 0)
			j++;
	}
	return (j);
}

char	*rm_heredoc(char **cmd_sp, int i, int lock)
{
	char	*ret;
	int		x;
	int		flag;
	int		start;

	x = -1;
	ret = NULL;
	flag = 0;
	while (cmd_sp[++x] != NULL)
	{
		lock = 0;
		if ((ft_strnstr(cmd_sp[i], ">>", 2) && (int)ft_strlen(cmd_sp[i]) == 2)
				|| (ft_strnstr(cmd_sp[i], ">", 1) && (int)ft_strlen(cmd_sp[i]) == 1))
		{
			start = find_rm_size(cmd_sp[i + 1], -1, 0, &lock) + lock;
			if ((start != (int)ft_strlen(cmd_sp[i + 1])))
				ret = ft_strjoin_swap(ret, ft_substr(cmd_sp[i + 1], start, (int)ft_strlen(cmd_sp[i + 1]) - start));
			x += 2;
		}
		else if (ft_strnstr(cmd_sp[i], ">>", 2) && (int)ft_strlen(cmd_sp[i]) > 2)
		{
			start = find_rm_size(ft_strchr2(cmd_sp[i], '>'), -1, 0, &lock) + lock;
			if ((start != (int)ft_strlen(ft_strchr2(cmd_sp[i], '>'))))
				ret = ft_strjoin_swap(ret, ft_substr(ft_strchr2(cmd_sp[i], '>'), start, (int)ft_strlen(ft_strchr2(cmd_sp[i], '>')) - start));
			x++;
		}
		else if (ft_strnstr(cmd_sp[i], ">", 1) && (int)ft_strlen(cmd_sp[i]) > 1)
		{
			start = find_rm_size(ft_strchr(cmd_sp[i], '>'), -1, 0, &lock) + lock;
			if ((start != (int)ft_strlen(ft_strchr(cmd_sp[i], '>'))))
				ret = ft_strjoin_swap(ret, ft_substr(ft_strchr(cmd_sp[i], '>'), start, (int)ft_strlen(ft_strchr(cmd_sp[i], '>')) - start));
			x++;
		}
	}
	return (ret);
}
/*
char	*rm_heredoc(char **cmd_sp, int i)
{
	char	*ret;
	int		x;

	x = -1;
	ret = NULL;
	while (cmd_sp[++x] != NULL)
	{
		if (ft_str2chr(cmd_sp[x], '>') && x == i)
		{
			if (!ret)
				ret  = ft_strdup(ft_str2chr(cmd_sp[x], '>'));
			else
				ret = ft_strjoin_swap(ret, ft_str2chr(cmd_sp[x], '>'));
		}
		else if (x == i && (cmd_sp[x][0] != '<' && cmd_sp[x][0] != '>'))
		{
			if (!ret)
				ret  = ft_strinit(cmd_sp[x], '<');
			else
				ret = ft_strjoin_swap(ret, ft_strinit(cmd_sp[x], '<'));
		}
		else if ((x != i) || (x != i && x -1 != i))
		{
			if (!ret)
				ret = ft_strdup(cmd_sp[x]);
			else
				ret = ft_strjoin_swap(ret, cmd_sp[x]);
			printf("ret:	%s\n", ret);
		}
		ret = ft_strjoin_swap(ret, " ");
	}
	//printf("=	%s$\n", ret);
	return (ret);
}*/