/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_used.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 19:40:56 by vifernan          #+#    #+#             */
/*   Updated: 2022/12/20 20:27:18 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_swap(char	*ret, char	*str, int flag)
{
	char	*aux;

	aux = NULL;
	if (!ret)
		ret = ft_strdup(str);
	else
	{
		aux = ft_strdup(ret);
		free(ret);
		ret = ft_strjoin(aux, str);
		free (aux);
	}
	if (flag)
		free(str);
	return (ret);
}

char	*ret_value(char *ret)
{
	int	i;
	int	x;

	i = -1;
	x = 0;
	while (ret[++i] != '\0')
		if (ret[i] == ' ')
			x++;
	if (x == i)
	{
		free(ret);
		return (NULL);
	}
	return (ret);
}

char	*find_middle(char *str, int type)
{
	int		init;
	int		end;
	char	*aux;
	char	*ret;

	init = find_rm_size(str, 0, 0, type);
	end = 0;
	while (str[init + end] == '>' || str[init + end] == '<')
		end++;
	aux = ft_substr(str, 0, init);
	init += end;
	ret = ft_strdup(aux);
	free(aux);
	aux = ft_strjoin(ret, " ");
	free (ret);
	end = find_rm_size((char *)str + init, 0, 0, 5);
	ret = ft_strjoin(aux, (char *)str + end + init);
	free(aux);
	return (ret);
}

char	*rm_used(char **cmd_sp, int i, int type, int size)
{
	char	*ret;
	int		x;

	x = -1;
	ret = NULL;
	while (cmd_sp[++x] != NULL)
	{
		if (x != i)
			ret = join_swap(ret, cmd_sp[x], 0);
		else
		{
			ret = join_swap(ret, find_middle(cmd_sp[x], type), 1);
			if ((int)ft_strlen(cmd_sp[x]) == size)
				x++;
		}
		ret = join_swap(ret, " ", 0);
		if (cmd_sp[x] == NULL)
			break ;
	}
	return (ret_value(ret));
}
