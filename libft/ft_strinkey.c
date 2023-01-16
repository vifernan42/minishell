/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strinkey.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:29:30 by vifernan          #+#    #+#             */
/*   Updated: 2023/01/16 19:40:02 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "libft.h"
int ft_strinkey(const char *str, const char *key)
{
    int         i;
    int         j;
    
    i = -1;
    if (key == NULL || str == NULL)
        return (-1);
    while (str[++i] != '\0')
    {
        j = -1;
        while (key[++j] != '\0')
        {
            if (str[i] == key[j])
                return (i);
        }           
    }
    return (-1);
}