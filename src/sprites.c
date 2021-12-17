/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiranda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 07:42:43 by tmiranda          #+#    #+#             */
/*   Updated: 2021/04/07 13:36:22 by tmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_start(t_drsp *drsp, t_sprite *spr, t_player *pl, int i)
{
	drsp->spr_x = spr[i].x - pl->x;
	drsp->spr_y = spr[i].y - pl->y;
	drsp->inv_det = 1.0 / (-pl->dir_y * pl->plane_x + pl->dir_x * pl->plane_y);
	drsp->tr_x = drsp->inv_det * (pl->dir_y * drsp->spr_x
			- pl->dir_x * drsp->spr_y);
	drsp->tr_y = drsp->inv_det * (pl->plane_y
			* drsp->spr_x - pl->plane_x * drsp->spr_y);
	drsp->spr_scr_x = (int)((drsp->w / 2) * (1 + drsp->tr_x / drsp->tr_y));
	drsp->v_movescreen = (int)(V_MOVE / drsp->tr_y);
	drsp->spr_h = abs((int)(drsp->h / drsp->tr_y)) / V_DIV;
	drsp->start_y = drsp->h / 2 - drsp->spr_h / 2 + drsp->v_movescreen;
	if (drsp->start_y < 0)
		drsp->start_y = 0;
	drsp->end_y = drsp->spr_h / 2 + drsp->h / 2 + drsp->v_movescreen;
	if (drsp->end_y >= drsp->h)
		drsp->end_y = drsp->h - 1;
	drsp->spr_w = abs((int)(drsp->w / drsp->tr_y)) / U_DIV;
	drsp->start_x = drsp->spr_scr_x - drsp->spr_w / 2;
	if (drsp->start_x < 0)
		drsp->start_x = 0;
	drsp->end_x = drsp->spr_w / 2 + drsp->spr_scr_x;
	if (drsp->end_x >= drsp->w)
		drsp->end_x = drsp->w;
}

void	calc_end(int stripe, t_vars *vars, t_drsp *drsp, float z)
{
	int				tex_x;
	int				tex_y;
	int				y;
	unsigned int	color;
	int				d;

	tex_x = (int)(256 * (stripe - (drsp->spr_scr_x - drsp->spr_w / 2))
			* vars->text.sp.width / drsp->spr_w) / 256;
	if (drsp->tr_y > 0 && stripe >= 0 && stripe < drsp->w && drsp->tr_y < z)
	{
		y = drsp->start_y;
		while (y < drsp->end_y)
		{
			d = (y - drsp->v_movescreen) * 256 - drsp->h * 128
				+ drsp->spr_h * 128;
			tex_y = ((d * vars->text.sp.height) / drsp->spr_h) / 256;
			if (tex_x >= 0 && tex_y >= 0)
				color = my_mlx_pixel_take(&vars->text.sp, tex_x, tex_y);
			if (color != 0 && color <= 16777215)
				my_mlx_pixel_put(&vars->data, stripe, y + 1, color);
			y++;
		}
	}
}

void	draw_sprite(t_vars *vars)
{
	int		i;
	int		stripe;
	float	z;

	i = 0;
	vars->drsp.w = vars->cub.w;
	vars->drsp.h = vars->cub.h;
	while (i < vars->k)
	{
		calc_start(&vars->drsp, vars->spr, &vars->pl, i);
		stripe = vars->drsp.start_x;
		while (stripe < vars->drsp.end_x)
		{
			z = vars->z_buffer[stripe];
			calc_end(stripe, vars, &vars->drsp, z);
			stripe++;
		}
		i++;
	}
}

void	sort_sprite(int k, t_sprite *spr)
{
	int			i;
	int			j;
	t_sprite	tmp;

	i = 0;
	while (i < k)
	{
		j = 0;
		while (j < k - i - 1)
		{
			if (spr[j + 1].dist > spr[j].dist)
			{
				tmp = spr[j];
				spr[j] = spr[j + 1];
				spr[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	calc_dist_sprite(int k, t_sprite *spr, t_player *pl)
{	
	int	i;

	i = 0;
	while (i < k)
	{
		spr[i].dist = ((pl->x - spr[i].x)*(pl->x - spr[i].x)
				+ (pl->y - spr[i].y)*(pl->y - spr[i].y));
		i++;
	}
	sort_sprite(k, spr);
}
