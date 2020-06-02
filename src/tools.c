#include "doom-nukem.h"

double     calc_dist(t_point a, t_point b)
{
    double res;

    res = (b.x - a.x) * (b.x - a.x) 
    + (b.y - a.y) * (b.y - a.y);
    return (sqrt(res));
}

void		ft_exit(t_var *info, t_render *render)
{
    
}

