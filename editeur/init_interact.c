/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_interact.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewis <lewis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/02/20 15:23:17 by lewis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem_edit.h"

int		get_map_size(t_input_edit *input_edit)
{
	char	*line;
	int		size;
	
	(void)input_edit;
	ft_putendl("Map size?");
	size = 0;
	while(size < 10)
	{
		get_next_line(0, &line);
		size = ft_atoi(line);
		if (size < 10)
			ft_putendl("Wrong size, try something else");
	}
	return (size);
}