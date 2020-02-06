/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 13:32:17 by lbonnete          #+#    #+#             */
/*   Updated: 2018/11/21 16:05:47 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putnbr_fd(int n, int fd)
{
	long l;
	char c;

	l = n;
	if (l < 0)
	{
		write(fd, "-", 1);
		l = -l;
	}
	if (l > 9)
		ft_putnbr_fd(l / 10, fd);
	c = l % 10 + '0';
	write(fd, &c, 1);
}
