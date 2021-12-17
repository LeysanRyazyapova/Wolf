/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiranda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 12:46:55 by tmiranda          #+#    #+#             */
/*   Updated: 2021/04/07 12:48:20 by tmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
void	rotate_left(t_player *pl)
{
	float	old_dir_x;
	float	old_plane_x;
	float	rot_speed;

	rot_speed = 0.05;
	old_dir_x = pl->dir_x;
	pl->dir_x = pl->dir_x * cos(-rot_speed) - pl->dir_y * sin(-rot_speed);
	pl->dir_y = old_dir_x * sin(-rot_speed) + pl->dir_y * cos(-rot_speed);
	old_plane_x = pl->plane_x;
	pl->plane_x = pl->plane_x * cos(-rot_speed) - pl->plane_y * sin(-rot_speed);
	pl->plane_y = old_plane_x * sin(-rot_speed) + pl->plane_y * cos(-rot_speed);
}

void	rotate_right(t_player *pl)
{
	float	old_dir_x;
	float	old_plane_x;
	float	rot_speed;

	rot_speed = 0.05;
	old_dir_x = pl->dir_x;
	pl->dir_x = pl->dir_x * cos(rot_speed) - pl->dir_y * sin(rot_speed);
	pl->dir_y = old_dir_x * sin(rot_speed) + pl->dir_y * cos(rot_speed);
	old_plane_x = pl->plane_x;
	pl->plane_x = pl->plane_x * cos(rot_speed) - pl->plane_y * sin(rot_speed);
	pl->plane_y = old_plane_x * sin(rot_speed) + pl->plane_y * cos(rot_speed);
}
