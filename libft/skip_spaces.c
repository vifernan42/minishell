/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_spaces.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:05:32 by vifernan          #+#    #+#             */
/*   Updated: 2022/07/21 17:29:18 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*sk_front(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = (int)ft_strlen(str) - 1;
	while (str[j] == ' ' && j >= 0)
	{
		i++;
		j--;
	}
	return (ft_substr(str, 0, (int)ft_strlen(str) - i));

}

char	*skip_spaces(char *str)
{
	int	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] == ' ')
		i++;
	return (sk_front(ft_substr(str, i, (int)ft_strlen(str) - i)));
}
/*
int main()
{
	printf(">%s\n", skip_spaces("        hola como estas            "));
}*/
