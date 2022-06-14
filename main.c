/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:36:59 by ialvarez          #+#    #+#             */
/*   Updated: 2022/05/24 18:38:25 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <readline/readlline.h>
#include <readline/history.h>

int main(void)
{
	while(1)
	{
		char * str = readline ("minishell: $ ");
		free (str);
	}
}
