/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_spaces.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:05:32 by vifernan          #+#    #+#             */
/*   Updated: 2022/07/27 19:44:23 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

/*void	leaks3(void)
{
	system("leaks minishell");
	printf("Entra\n");
}*/

char	*sk_front(char *str)
{
	int		i;
	int		j;
	char	*aux;

	i = 0;
	j = (int)ft_strlen(str) - 1;
	while (str[j] == ' ' && j >= 0)
	{
		i++;
		j--;
	}
	aux = ft_strdup(str);
	free(str);
	str = ft_substr(aux, 0, (int)ft_strlen(aux) - i);
	free(aux);
	return (str);
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
	aux = ft_strdup(str);
	free(str);
	str = ft_substr(aux, i, (int)ft_strlen(aux) - i);
	free(aux);
	return (sk_front(str));
}
/*
int main()
{
	printf(">%s\n", skip_spaces("        hola como estas            "));
}*/
