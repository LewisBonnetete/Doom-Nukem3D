#include "../inc/doom-nukem.h"

t_var   init_var(char *str)
{
    ;
}

int     play(char *file, char *str)
{
    t_raycast   fenetre; // x0, x1, y0, y1, secteur

    check_input(str);
    t_var info;  
    init_var(str) // rempli info
    fenetre.xo = 0;
    fenetre.x1 = WINDOW_W;
    fenetre.y0 = 0;
    fenetre.y1 = WINDOW_H;
    init_infos(&info, str);
    algo(&info; fenetre);
}

    /*
    ** a rajouter dans info
    **       t_player    player = pos, dir, fov, secteur
    */

int     algo(t_var *info, t_raycast fenetre)
{
    


    t_ray      ray; // cam_x, dir, hit_portal, hit_wall
    t_wall      wall;
    int         x;
    int         n;

    x = fenetre.x0;
    init_ray(ray);
    n = -1;
    while(x < fenetre.x1)//casting rays
    {
        wall = fenetre.secteur.wall; 
        while(++n < fenetre.secteur.nbr_walls)
        {
            wall = fenetre.sector.wall[n]; //a faitre
            if(intersect(ray, wall) == 1)
            {
                get_projection_of_wall(info, wall, fenetre, ray); // fentre.x1,y1,y2
                    // si new_x1 > WINDOW_W, wall affichable qu'en partie
                    // si new_x1 = WINDOW_W, wall remplit la fin de l'ecran
                    // idem pour y1.
                if(wall.is_portal)
                {
                    fenetre.x0 = x;
                    fenetre.secteur = wall.sector_next;
                    algo(info, fenetre);
                    if (wall.is_transparent)
                        draw_portal_texture(info, wall, fenetre, ray);
                    if (wall.is_textured)
                        draw_portal_fill(info, wall, fenetre, ray);
                    x = fenetre.x1;
                }
                else
                {
                    draw_wall(info, fenetre, wall, ray);
                    ray.hit_wall = 1;
                    x = fenetre.x1;
                }
                break;
            }
        }
        draw_floor_or_ceilling(info, fenetre, ray);
    }
}

int     wall_intersec(int wall, int x, t_var *info)
{

}