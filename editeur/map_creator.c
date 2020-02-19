/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/02/19 15:38:50 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem_edit.h"

int		open_package()
{
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