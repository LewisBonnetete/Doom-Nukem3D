/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewis <lewis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 17:37:57 by lbonnete          #+#    #+#             */
/*   Updated: 2020/02/21 15:13:48 by lewis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem_edit.h"

int		open_package()
{
	int fd;
	
	if (-1 == (fd = open("package", O_RDWR)))
	{
		close(fd);
		return (-1);
	}
	if (-1 == lseek(fd, 1, SEEK_END))
	{
		close(fd);
		return (-1);
	}
	return (fd);
}