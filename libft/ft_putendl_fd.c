/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 13:45:16 by lbonnete          #+#    #+#             */
/*   Updated: 2019/10/02 13:43:56 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putendl_fd(char const *str, int fd)
{
	int i;

	if (str)
	{
		i = 0;
		while (str[i++])
			;
		write(fd, str, i - 1);
		write(fd, "\n", 1);
	}
}
