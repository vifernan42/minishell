/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_nbsp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talentum <talentum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 19:26:38 by vifernan          #+#    #+#             */
/*   Updated: 2023/03/05 21:03:49 by talentum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*change_nbsp(char *str)
{
	char	*s;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] >= 32 && str[i] <= 126)
			j++;
	}
	s = malloc(sizeof(char) * j + 1);
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] >= 32 && str[i] <= 126)
			s[j++] = str[i];
	}
	s[j] = '\0';
	free(str);
	return (s);
}
