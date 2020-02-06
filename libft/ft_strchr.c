/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 14:20:57 by lbonnete          #+#    #+#             */
/*   Updated: 2018/12/04 17:30:46 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	size_t i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != c)
		if (s[i++] == 0)
			return (0);
	return ((char *)&s[i]);
}
