/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charindex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:55:35 by vifernan          #+#    #+#             */
/*   Updated: 2022/12/14 16:58:29 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_charindex(char *str, char c)
{
    int i;

    i = -1;
    if (!str || c == '\0')
        return (-1);
    while (str[++i] != '\0')
    {
        if (str[i] == c)
            return (i);
    }
    return (-1);
}