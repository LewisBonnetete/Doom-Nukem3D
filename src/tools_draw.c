#include "doom_nukem.h"

void		rgb_cap(t_rgb *rgb)
{
	if (rgb->r >= 255)
		rgb->r = 255;
	if (rgb->g >= 255)
		rgb->g = 255;
	if (rgb->b >= 255)
		rgb->b = 255;
}
