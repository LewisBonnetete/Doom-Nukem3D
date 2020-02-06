/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 14:39:14 by lbonnete          #+#    #+#             */
/*   Updated: 2018/11/24 15:46:51 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *ens, const char *x)
{
	int		i;

	i = 0;
	if (x[0] == 0)
		return ((char *)ens);
	while (((char *)ens)[i])
	{
		if (!(ft_strncmp(&(ens[i]), x, ft_strlen(x))))
			return ((char *)(&(ens[i])));
		i++;
	}
	return (0);
}
