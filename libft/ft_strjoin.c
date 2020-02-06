/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 18:30:57 by lbonnete          #+#    #+#             */
/*   Updated: 2018/12/05 13:59:33 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	char	*r;
	size_t	l1;
	size_t	l2;

	if (!s1 && !s2)
		return (0);
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	if (!(r = (char *)malloc(l1 + l2 + 1)))
		return (0);
	r[l1 + l2] = 0;
	i = 0;
	while (i < l1)
	{
		r[i] = s1[i];
		i++;
	}
	while (i < l1 + l2)
	{
		r[i] = s2[i - l1];
		i++;
	}
	r[i] = 0;
	return (r);
}
