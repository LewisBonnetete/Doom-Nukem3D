/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 18:57:29 by lbonnete          #+#    #+#             */
/*   Updated: 2018/11/21 16:42:59 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdlib.h>

static	size_t	info(char const *s, size_t *len, size_t *start, size_t *end)
{
	*len = ft_strlen(s);
	*end = *len - 1;
	while ((s[*start] == ' ' || s[*start] == '\n' || s[*start] == '\t')
	&& (*start < (*len / 2)))
		*start = *start + 1;
	while ((s[*end] == ' ' || s[*end] == '\n' || s[*end] == '\t')
	&& (*end >= (*len / 2)))
		*end = *end - 1;
	return (end - start + 1);
}

char			*ft_strtrim(char const *s)
{
	size_t	len;
	size_t	start;
	size_t	end;
	char	*r;

	if (!(s))
		return (0);
	len = 0;
	start = 0;
	end = 0;
	if (s[0] == 0)
	{
		if (!(r = (char *)malloc(1)))
			return (0);
		r[0] = 0;
		return (r);
	}
	if (!(r = (char *)malloc(info(s, &len, &start, &end))))
		return (0);
	r[start - end] = 0;
	len = 0;
	while (start <= end)
		r[len++] = s[start++];
	r[len] = 0;
	return (r);
}
