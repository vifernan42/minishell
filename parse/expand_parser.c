/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:43:08 by vifernan          #+#    #+#             */
/*   Updated: 2023/02/15 20:56:23 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*value_to_expand(t_data *data, char *str, int i, int *char_index)
{
	char	*aux;
	char	*var_name;
	char	*var_env;

	*char_index = ft_strinkey(str + i, "$,. ><-@?¿¡/\\%#·\"\'");
	if (*char_index == 0 && str[i] == '?')
		*char_index = 1;
	var_name = ft_substr(str + i, 0, *char_index);
	var_env = ft_strjoin(var_name, "=");
	free(var_name);
	var_name = search_variable(data->env, var_env);
	if (!var_name)
		var_name = "";
	free(var_env);
	aux = ft_substr(str, 0, i - 1);
	var_env = ft_strjoin(aux, var_name);
	free(aux);
	return (var_env);
}

static int	change_value(char *str, int i, t_data *data, char **expand_ln)
{
	int		char_index;
	char	*value;
	char	*aux;

	value = value_to_expand(data, str, i, &char_index);
	free(*expand_ln);
	if (char_index > 0)
	{
		aux = ft_substr(str, (i + char_index),
				(int)ft_strlen(str) - (i + char_index));
		*expand_ln = ft_strjoin(value, aux);
		free(aux);
	}
	else
		*expand_ln = ft_strdup(value);
	free(value);
	free(str);
	return (0);
}

static int	check_before_change(char *str, int i, int *here, int *open)
{
	if (i > 0 && str[i] == '<' && str[i - 1] == '<')
		*here = 1;
	else if (str[i] != '\'' && str[i] != '\"' && str[i] != ' ' && str[i] != '$')
		*here = 0;
	if (str[i] == '\'')
	{
		if (*open)
			*open = 0;
		else
			*open = 1;
	}
	if (!*open && !*here)
		return (0);
	else
		return (1);
}

char	*take_variable(t_data *data, char *str)
{
	int		i;
	int		open;
	char	*expand_ln;
	int		here;

	i = -1;
	open = 0;
	expand_ln = NULL;
	here = 0;
	while (str[++i] != '\0')
	{
		if (!check_before_change(str, i, &here, &open) && str[i] == '$')
		{
			i = change_value(ft_strdup(str), i + 1, data, &expand_ln);
			if (expand_ln)
			{
				free(str);
				str = ft_strdup(expand_ln);
			}
		}
	}
	if (expand_ln)
		free(expand_ln);
	return (str);
}
