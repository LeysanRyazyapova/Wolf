/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiranda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 16:30:52 by tmiranda          #+#    #+#             */
/*   Updated: 2021/04/04 17:57:32 by tmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
void	set_cam_plane(t_camera *cam, t_map *cub, t_player *pl, int i)
{	
	cam->camera_x = (2 * i) / (float)cub->w - 1;
	cam->ray_x = pl->dir_x - pl->plane_x * cam->camera_x;
	cam->ray_y = pl->dir_y - pl->plane_y * cam->camera_x;
	cam->step_x = fabsf(1 / cam->ray_x);
	cam->step_y = fabsf(1 / cam->ray_y);
}

void	set_tile_step(t_camera *cam, t_player *pl)
{
	if (cam->ray_x < 0)
	{
		cam->tile_x = -1;
		cam->xintercept = (pl->x - floor(pl->x)) * cam->step_x;
	}
	else
	{
		cam->tile_x = 1;
		cam->xintercept = (floor(pl->x) + 1.0 - pl->x) * cam->step_x;
	}
	if (cam->ray_y < 0)
	{
		cam->tile_y = -1;
		cam->yintercept = (pl->y - floor(pl->y)) * cam->step_y;
	}
	else
	{
		cam->tile_y = 1;
		cam->yintercept = (floor(pl->y) + 1 - pl->y) * cam->step_y;
	}	
}

void	hit_wall(t_camera *cam, t_map *cub, t_player *pl)
{
	int	hit;

	hit = 0;
	cam->mapX = (int)pl->x;
	cam->mapY = (int)pl->y;
	while (hit == 0)
	{
		if (cam->xintercept < cam->yintercept)
		{
			cam->xintercept += cam->step_x;
			cam->mapX += cam->tile_x;
			cam->s = 0;
		}
		else
		{
			cam->yintercept += cam->step_y;
			cam->mapY += cam->tile_y;
			cam->s = 1;
		}
		if (cub->map[cam->mapY][cam->mapX] == '1')
			hit = 1;
	}
}

void	calc_dist(t_camera *cam, t_player *pl)
{
	if (cam->s == 0)
		cam->dist = (cam->mapX - pl->x + (1 - cam->tile_x) / 2) / cam->ray_x;
	else
		cam->dist = (cam->mapY - pl->y +(1 - cam->tile_y) / 2) / cam->ray_y;
}

void	cast_ray(t_vars *vars)
{
	int	i;

	i = 0;
	if (vars->cub.err == 1)
	{
		printf("Error\nMap isn't valid");
		exit(0);
	}
	else
	{
		calc_dist_sprite(vars->k, vars->spr, &vars->pl);
		while (i < vars->cub.w)
		{
			set_cam_plane(&vars->cam, &vars->cub, &vars->pl, i);
			set_tile_step(&vars->cam, &vars->pl);
			hit_wall(&vars->cam, &vars->cub, &vars->pl);
			calc_dist(&vars->cam, &vars->pl);
			draw(vars, i);
			vars->z_buffer[i] = vars->cam.dist;
			i++;
		}
		draw_sprite(vars);
	}
	if (vars->save == 0)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->data.img, 0, 0);
}
