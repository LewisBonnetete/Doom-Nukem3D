/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 14:39:14 by lbonnete          #+#    #+#             */
/*   Updated: 2018/11/21 16:10:57 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strnstr(const char *ens, const char *x, size_t n)
{
	int		i;
	int		j;

	i = 0;
	if (x[0] == 0)
		return ((char *)ens);
	while (((char *)ens)[i] && i < (int)n)
	{
		j = 0;
		while (((char *)ens)[i + j] == x[j] && (i + j) < (int)n)
			if (!(x[++j]))
				return (&((char *)ens)[i]);
		i++;
	}
	return (0);
}
