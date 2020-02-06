/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 16:33:29 by lbonnete          #+#    #+#             */
/*   Updated: 2018/11/21 16:01:39 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	void	*ret;
	size_t	i;

	i = 0;
	if (!(ret = malloc(size)))
		return (NULL);
	while (i < size)
	{
		((char *)ret)[i] = 0;
		i++;
	}
	return (ret);
}
