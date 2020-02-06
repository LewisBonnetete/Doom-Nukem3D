/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 17:04:55 by lbonnete          #+#    #+#             */
/*   Updated: 2019/10/02 13:45:30 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_sqrt(int nb)
{
	int i;
	int gap;
	int som;

	i = 1;
	som = 0;
	gap = 1;
	if (nb <= 0)
		return (0);
	while (som <= nb && i < 46340)
	{
		som = som + gap;
		if (som == nb)
			return (i);
		gap = gap + 2;
		i++;
	}
	return (0);
}
