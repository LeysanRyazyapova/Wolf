/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiranda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 10:19:41 by tmiranda          #+#    #+#             */
/*   Updated: 2021/04/07 10:25:23 by tmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_xpm(char *str, t_map *cub)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	i -= 4;
	if (ft_strncmp(str + i, ".xpm", 4))
		cub->err = 1;
}

void	check_fd(char *str, t_map *cub)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd < 0)
		cub->err = 1;
	close(fd);
}

int	check_param_count(t_map *cub)
{
	if (cub->flag[0] == 0 || cub->flag[1] == 0 || cub->flag[2] == 0
		|| cub->flag[3] == 0 || cub->flag[4] == 0 || cub->flag[5] == 0
		|| cub->flag[6] == 0 || cub->flag[7] == 0)
		return (0);
	return (1);
}

void	draw_center(t_vars *vars, int x, int y)
{
	int				tex_y;
	unsigned int	color;

	tex_y = (int)vars->draw.tex_pos;
	vars->draw.tex_pos += vars->draw.step;
	color = my_mlx_pixel_take(&vars->draw.current,
			vars->draw.current.width - vars->draw.tex_x - 1, tex_y);
	if (color <= 16777215)
		my_mlx_pixel_put(&vars->data, x, y, color);
	else
		my_mlx_pixel_put(&vars->data, x, y, 0x00FFFFFF);
}

void	check_texture(t_map *cub)
{
	check_xpm(cub->no, cub);
	check_xpm(cub->so, cub);
	check_xpm(cub->ea, cub);
	check_xpm(cub->we, cub);
	check_xpm(cub->s, cub);
	check_fd(cub->no, cub);
	check_fd(cub->so, cub);
	check_fd(cub->ea, cub);
	check_fd(cub->we, cub);
	check_fd(cub->s, cub);
}
