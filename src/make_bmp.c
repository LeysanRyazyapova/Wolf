/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiranda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 11:32:59 by tmiranda          #+#    #+#             */
/*   Updated: 2021/04/07 11:37:41 by tmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	setzero(unsigned char *bmp, int c)
{
	int	i;

	i = 0;
	while (i < c)
	{
		bmp[i] = 0;
		i++;
	}
}

void	bits_shift(unsigned char *bmp, unsigned int c)
{
	bmp[0] = (unsigned char)(c);
	bmp[1] = (unsigned char)(c >> 8);
	bmp[2] = (unsigned char)(c >> 16);
	bmp[3] = (unsigned char)(c >> 24);
}

int	bitmapfileheader(t_vars *vars, int fd)
{
	unsigned char	bmp[54];
	int				filesize;

	setzero(bmp, 54);
	filesize = 54 + 4 * vars->cub.w * vars->cub.h;
	bmp[0] = (unsigned char) 'B';
	bmp[1] = (unsigned char) 'M';
	bits_shift(bmp + 2, filesize);
	bmp[10] = (unsigned char)54;
	bmp[14] = (unsigned char)40;
	bits_shift(bmp + 18, vars->cub.w);
	bits_shift(bmp + 22, vars->cub.h);
	bmp[26] = (unsigned char)1;
	bmp[28] = (unsigned char)32;
	write (fd, bmp, 54);
	if (fd < 0)
		return (0);
	else
		return (1);
}

int	bitmapimg(t_vars *vars, int fd)
{
	int				x;
	int				y;
	unsigned int	color;
	unsigned char	bmp[4];

	setzero(bmp, 4);
	y = vars->cub.h - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < vars->cub.w)
		{
			color = *(unsigned int *)(vars->data.addr + (y * vars->data.length
						+ x * (vars->data.bpp / 8)));
			bits_shift(bmp, color);
			write(fd, bmp, 4);
			x++;
		}
		y--;
	}
	return (1);
}

int	make_bmp(t_vars *vars)
{
	int	file;

	vars->save = 1;
	initialisation(vars);
	cast_ray(vars);
	file = open("screen.bmp", O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	if (file < 0)
		return (0);
	if (!bitmapfileheader(vars, file))
		return (0);
	if (!bitmapimg(vars, file))
		return (0);
	close (file);
	return (1);
}
