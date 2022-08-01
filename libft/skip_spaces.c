/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_spaces.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:05:32 by vifernan          #+#    #+#             */
/*   Updated: 2022/08/01 15:06:01 by ialvarez         ###   ########.fr       */
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

	aux = NULL; /*no necesario*/
	i = 0;
	j = ft_strlen(str) - 1;
	while (str[j] == ' ' && j >= 0)
	{
		i++;
		j--;
	}
	aux = ft_strdup(str);
	free(str);
	str = ft_substr(aux, 0, ft_strlen(aux) - i);
	free(aux);
	return (str);
}

char	*skip_spaces(char *str)
{
	int		i;
	char	*aux;

	aux = NULL; /*no es necesario*/
	if (!str)
		return (NULL);
	i = 0;
	while (str[i] == ' ')
		i++;
	aux = ft_strdup(str);
//	free(str);				/*este no nos gusta hay que quitarlo*/
	str = ft_substr(str, i, ft_strlen(aux) - i);
	free(aux);
	return (sk_front(str));
}
/*
int main()
{
	printf(">%s\n", skip_spaces("        hola como estas            "));
}*/
