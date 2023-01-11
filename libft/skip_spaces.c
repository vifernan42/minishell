/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_spaces.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:05:32 by vifernan          #+#    #+#             */
/*   Updated: 2023/01/10 18:11:48 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include "../minishell.h"
/*
char	*set_dollar_value(char *str)
{
	int	i;
	char	*var_name;
	int		char_index;
	char	*var_env;

	i = -1;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			char_index = ft_charindex(str + i, ' ') - 1;
			if (ft_charindex(str + i, '\'') - 1 < char_index)
				char_index = ft_charindex(str + i, '\'') - 1;
			if (char_index > 0)
				var_name = ft_substr(str + i, 1, char_index);
			else
			{
				char_index = ft_charindex(str + i, '\"');
				var_name = ft_substr(str + i, 1, char_index - 1);
			}
			var_env = var_name;
			free(var_name);
			var_name = ft_strjoin(var_env, "=");
			var_env = search_variable(env, var_name);
		}
	}
	return (NULL);
}*/

char	*sk_front(char *str)
{
	int		i;
	int		j;
	char	*aux;

	i = 0;
	j = ft_strlen(str) - 1;
	if (j == 0)
		return (str);
	while (j >= 0)
	{
		if (str[j] == ' ')
			i++;
		else
			break ;
		j--;
	}
	aux = ft_substr(str, 0, ft_strlen(str) - i);
	free(str);
	//char *hola;
	//hola = set_dollar_value(aux);
	return (aux);
}

char	*skip_spaces(char *str)
{
	int		i;
	char	*aux;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] == ' ')
		i++;
	aux =  ft_substr(str, i, ft_strlen(str) - i);
	return (sk_front(aux));
}