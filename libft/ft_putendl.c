/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 19:50:28 by lbonnete          #+#    #+#             */
/*   Updated: 2018/12/04 17:40:45 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putendl(char const *str)
{
	int i;

	if (str)
	{
		i = 0;
		while (str[i++])
			;
		write(1, str, i - 1);
	}
	write(1, "\n", 1);
}
