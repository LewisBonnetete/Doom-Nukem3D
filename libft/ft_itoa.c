/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 19:02:02 by lbonnete          #+#    #+#             */
/*   Updated: 2018/11/21 15:54:09 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void		neg_update(int *neg, int *n, int *len)
{
	*neg = 1;
	*n = -1 * *n;
	*len = *len + 1;
}

static	char	*specialcase(char *res, int n)
{
	if (n == -2147483648)
	{
		if (!(res = (char *)malloc(12)))
			return (0);
		return (intmin(res));
	}
	if (n == 0)
	{
		if (!(res = (char *)malloc(2)))
			return (0);
		res[0] = '0';
		res[1] = 0;
		return (res);
	}
	return (0);
}

char			*ft_itoa(int n)
{
	char	*res;
	int		len;
	int		neg;

	res = 0;
	neg = 0;
	len = ft_intlen(n);
	if (n == -2147483648 || n == 0)
		return (specialcase(res, n));
	if (n < 0)
		neg_update(&neg, &n, &len);
	if (!(res = (char *)malloc(len + 1)))
		return (0);
	res[len--] = 0;
	if (neg)
		res[0] = '-';
	while (n)
	{
		res[len--] = n % 10 + '0';
		n = n / 10;
	}
	return (res);
}
