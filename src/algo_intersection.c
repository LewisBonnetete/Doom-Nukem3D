/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_intersection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 17:04:28 by lewis             #+#    #+#             */
/*   Updated: 2020/07/17 15:01:08 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
** calc_wall_spec details :
** si le mur est parallele a l'axe des ordonnées,
** on met 11111 sur wall->eq_slope
** et la valeur de l'abscisse sur wall->eq_cste
** utiliser cette fonction apres l'init des walls dans
** le parsing, au lieu de dans la fnc intersct
*/

void	calc_wall_spec(t_wall *wall)
{
	if (wall->b.x != wall->a.x)
	{
		if (wall->a.y == wall->b.y)
			wall->eq_slope = 0;
		else
			wall->eq_slope =
				(double)(wall->b.y - wall->a.y) / (wall->b.x - wall->a.x);
		wall->eq_cste = (double)wall->a.y - wall->eq_slope * wall->a.x;
	}
	else
	{
		wall->eq_slope = 1111;
		wall->eq_cste = (double)wall->a.x;
	}
	wall->height = (double)(wall->c.z - wall->a.z);
}

int		xy_in_frontview(double x, double y, t_ray ray)
{
	if ((ray.dx > 0 && (x <= ray.x)) || (ray.dy > 0 && (y <= ray.y)) ||
	(ray.dx < 0 && (x >= ray.x)) || (ray.dy < 0 && (y >= ray.y)))
		return (0);
	return (1);
}

int		xy_in_ab(double x, double y, t_point a, t_point b)
{
	if (((a.x <= x && x <= b.x) || (b.x <= x && x <= a.x))
		&& ((a.y <= y && y <= b.y) || (b.y <= y && y <= a.y)))
		return (1);
	return (0);
}

int		ret_inter(t_ray *ray, t_wall *wall)
{
	if (ray->eq_slope == wall->eq_slope)
		return (0);
	if (xy_in_ab(ray->x2, ray->y2, wall->a, wall->b))
		return (xy_in_frontview(ray->x2, ray->y2, *ray));
	return (0);
}

int		intersect(t_ray *ray, t_wall *wall)
{
	calc_wall_spec(wall);
	if (wall->eq_slope == 1111)
	{
		ray->x2 = wall->eq_cste;
		ray->y2 = ray->eq_slope * ray->x2 + ray->eq_cste;
	}
	else if (ray->eq_slope == 1111)
	{
		ray->x2 = ray->x;
		ray->y2 = wall->eq_slope * ray->x2 + wall->eq_cste;
	}
	else if (wall->eq_slope == 0)
	{
		ray->x2 = (wall->eq_cste - ray->eq_cste)
		/ (ray->eq_slope);
		ray->y2 = wall->eq_cste;
	}
	else
	{
		ray->x2 = (wall->eq_cste - ray->eq_cste)
		/ (ray->eq_slope - wall->eq_slope);
		ray->y2 = ray->eq_slope * ray->x2 + ray->eq_cste;
	}
	return (ret_inter(ray, wall));
}
