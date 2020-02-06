/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 19:44:42 by lbonnete          #+#    #+#             */
/*   Updated: 2018/11/21 16:06:23 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putstr(char const *str)
{
	int i;

	i = 0;
	if (str)
	{
		while (str[i++])
			;
		write(1, str, i - 1);
	}
}
