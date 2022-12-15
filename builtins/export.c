/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 19:26:51 by ialvarez          #+#    #+#             */
/*   Updated: 2022/12/15 23:58:56 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_export(t_data *data, char *full_var)
{
	char	*var_name;
	char	*var_content;
	char	*var_full;

	var_name = ft_substr(full_var, 0, ft_charindex(full_var, '=') + 1);
	var_content = ft_substr(full_var, ft_charindex(full_var, '=') + 1, ft_strlen(full_var)); 
	var_full = ft_strjoin(var_name, var_content);
	env_update(data, var_full, var_name);
	free(var_name);
	free(var_content);
}

void	my_export(t_data *data, char **argv)
{
	int	i;
	
	i = 1;
	while (argv[i] != NULL)
	{
		if (ft_charindex(argv[i], '=') != -1 && ft_strlen(argv[i]) == 1)
			ft_printf("minishell: export: `=': not a valid identifier\n");
		else if (ft_charindex(argv[i], '=') != -1)
			do_export(data, argv[i]);
		i++;
	}
}