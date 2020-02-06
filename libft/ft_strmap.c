/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 16:57:48 by lbonnete          #+#    #+#             */
/*   Updated: 2018/11/21 16:10:01 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	char	*r;

	if (!(s))
		return (0);
	i = 0;
	while (s[i])
		i++;
	if (!(r = (char *)malloc(i + 1)))
		return (0);
	i = 0;
	while (s[i])
	{
		r[i] = f(s[i]);
		i++;
	}
	r[i] = 0;
	return (r);
}
