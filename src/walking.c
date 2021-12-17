/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiranda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 10:06:39 by tmiranda          #+#    #+#             */
/*   Updated: 2021/04/07 13:49:00 by tmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define SPEED 0.2
void	move_right(t_map *cub, t_player *pl)
{
	if (cub->map[(int)pl->y][(int)(pl->x - SPEED * pl->dir_y)] == '0')
		pl->x -= SPEED * pl->dir_y;
	if (cub->map[(int)(pl->y + pl->dir_x * SPEED)][(int)pl->x] == '0')
		pl->y += SPEED * pl->dir_x;
}

void	move_left(t_map *cub, t_player *pl)
{
	if (cub->map[(int)(pl->y - pl->dir_x * SPEED)][(int)pl->x] == '0')
		pl->y -= SPEED * pl->dir_x;
	if (cub->map[(int)pl->y][(int)(pl->x + pl->dir_y * SPEED)] == '0')
		pl->x += SPEED * pl->dir_y;
}

void	move_up(t_map *cub, t_player *pl)
{	
	if (cub->map[(int)pl->y][(int)(pl->x + pl->dir_x * SPEED)] == '0')
		pl->x += pl->dir_x * SPEED ;
	if (cub->map[(int)(pl->y + pl->dir_y * SPEED)][(int)pl->x] == '0')
		pl->y += pl->dir_y * SPEED;
}

void	move_down(t_map *cub, t_player *pl)
{
	if (cub->map[(int)pl->y][(int)(pl->x - pl->dir_x * SPEED)] == '0')
		pl->x -= SPEED * pl->dir_x;
	if (cub->map[(int)(pl->y - pl->dir_y * SPEED)][(int)pl->x] == '0')
		pl->y -= pl->dir_y * SPEED;
}

int	walking(t_vars *vars)
{	
	if (vars->key.key_esc == 1)
		exit(0);
	if (vars->key.key_d == 1)
		move_right(&vars->cub, &vars->pl);
	if (vars->key.key_a == 1)
		move_left(&vars->cub, &vars->pl);
	if (vars->key.key_w == 1)
		move_up(&vars->cub, &vars->pl);
	if (vars->key.key_s == 1)
		move_down(&vars->cub, &vars->pl);
	if (vars->key.key_r == 1)
		rotate_right(&vars->pl);
	if (vars->key.key_l == 1)
		rotate_left(&vars->pl);
	cast_ray(vars);
	return (1);
}
