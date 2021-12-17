/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolution.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiranda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 12:45:55 by tmiranda          #+#    #+#             */
/*   Updated: 2021/04/07 12:46:29 by tmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_screensize(t_map *cub)
{
	int	screen_w;
	int	screen_h;

	mlx_get_screen_size(&screen_w, &screen_h);
	if (cub->w > screen_w)
		cub->w = screen_w;
	if (cub->h > screen_h)
		cub->h = screen_h;
	if (cub->w < 1)
		cub->err = 1;
	if (cub->h < 1)
		cub->err = 1;
}
