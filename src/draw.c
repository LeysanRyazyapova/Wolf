/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiranda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 08:22:40 by tmiranda          #+#    #+#             */
/*   Updated: 2021/04/07 10:39:14 by tmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

unsigned int	my_mlx_pixel_take(t_data *data, int x, int y)
{
	char			*addr;

	addr = data->addr + (y * data->length + x * (data->bpp / 8));
	return (*(unsigned int *)addr);
}

void	current_tex(t_camera *cam, t_vars *vars, t_draw *draw)
{
	if (cam->s == 0 && cam->tile_x > 0)
		draw->current = vars->text.east;
	if (cam->s == 0 && cam->tile_x < 0)
		draw->current = vars->text.west;
	if (cam->s == 1 && cam->tile_y > 0)
		draw->current = vars->text.south;
	if (cam->s == 1 && cam->tile_y < 0)
		draw->current = vars->text.noth;
	if (cam->s == 0)
		draw->wall_x = vars->pl.y + vars->cam.dist * vars->cam.ray_y;
	else
		draw->wall_x = vars->pl.x + vars->cam.dist * vars->cam.ray_x;
	draw->wall_x -= floor(draw->wall_x);
	draw->tex_x = (int)(draw->wall_x * (float)draw->current.width);
	if ((cam->s == 0 && cam->ray_x > 0) || (cam->s == 1 && cam->ray_y < 0))
		draw->tex_x = draw->current.width - draw->tex_x - 1;
	if (draw->tex_x < 0)
		draw->tex_x = 0;
	if (draw->tex_x >= draw->current.width)
		draw->tex_x = draw->current.width - 1;
}

void	calc_wall(t_map *cub, t_camera *cam, t_draw *draw)
{
	draw->wall_h = cub->h / cam->dist;
	draw->start = (cub->h) / 2 - draw->wall_h / 2;
	if (draw->start < 0)
		draw->start = 0;
	draw->end = draw->wall_h / 2 + cub->h / 2;
	if (draw->end > cub->h)
		draw->end = cub->h - 1;
	draw->step = 1.0 * draw->current.height / draw->wall_h;
	draw->tex_pos = (draw->start - cub->h / 2 + draw->wall_h / 2) * draw->step;
}

void	draw(t_vars *vars, int x)
{
	int	y;

	y = 0;
	current_tex(&vars->cam, vars, &vars->draw);
	calc_wall(&vars->cub, &vars->cam, &vars->draw);
	while (y < vars->draw.start)
	{
		my_mlx_pixel_put(&vars->data, x, y, vars->cub.ceil);
		y++;
	}
	while (y < vars->draw.end)
	{
		draw_center(vars, x, y);
		y++;
	}
	while (y < vars->cub.h)
	{
		my_mlx_pixel_put(&vars->data, x, y, vars->cub.floor);
		y++;
	}
}
