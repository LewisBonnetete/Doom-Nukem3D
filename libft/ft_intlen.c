/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 19:06:54 by lbonnete          #+#    #+#             */
/*   Updated: 2018/11/21 15:53:16 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

size_t	ft_intlen(int nb)
{
	size_t i;

	i = 0;
	if (!(nb))
		return (1);
	while (nb)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}
