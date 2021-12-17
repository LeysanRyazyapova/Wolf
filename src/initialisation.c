/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiranda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 10:47:15 by tmiranda          #+#    #+#             */
/*   Updated: 2021/04/07 10:50:57 by tmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	initialisation(t_vars *vars)
{
	if (vars->save == 1)
	{
		if (vars->cub.w > 16384)
			vars->cub.w = 16384;
		if (vars->cub.h > 16384)
			vars->cub.h = 16384;
	}
	else
		check_screensize(&vars->cub);
	if (vars->cub.err != 1)
	{
		vars->z_buffer = (float *)malloc(sizeof(float) * vars->cub.w);
		vars->win = mlx_new_window(vars->mlx, vars->cub.w,
				vars->cub.h, "cub3D");
		vars->data.img = mlx_new_image(vars->mlx, vars->cub.w, vars->cub.h);
		vars->data.addr = mlx_get_data_addr(vars->data.img,
				&vars->data.bpp, &vars->data.length, &vars->data.endian);
	}
}

int	check_end(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	i -= 4;
	if (!ft_strncmp(".cub", (str + i), 5))
		return (0);
	return (1);
}
