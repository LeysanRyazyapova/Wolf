/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ceil_floor_color.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiranda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 10:41:45 by tmiranda          #+#    #+#             */
/*   Updated: 2021/04/07 10:45:10 by tmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_hex_color(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	parse_color(char *line, t_map *cub, int *color)
{
	int	i;
	int	col[3];

	i = 1;
	while (line[i] == ' ')
		i++;
	if (!get_num(line, &i, &col[0], ','))
		cub->err = 1;
	i++;
	if (!get_num(line, &i, &col[1], ','))
		cub->err = 1;
	i++;
	if (!get_num(line, &i, &col[2], '\0'))
		cub->err = 1;
	if (col[0] < 256 && col[1] < 256 && col[2] < 256)
		*color = get_hex_color(col[0], col[1], col[2]);
	else
	{
		printf("Error\nWrong color\n");
		cub->err = 1;
	}
}

void	parse_F(char *line, t_map *cub)
{
	if (line[0] == 'F' && line[1] == ' ')
	{
		if (cub->flag[6] == 0)
		{
			parse_color(line, cub, &cub->floor);
			cub->flag[6] = 1;
		}
		else
		{
			printf("Error\nToo many parameters floor color\n");
			cub->err = 1;
		}
	}	
}

void	parse_C(char *line, t_map *cub)
{
	if (line[0] == 'C' && line[1] == ' ')
	{
		if (cub->flag[7] == 0)
		{
			parse_color(line, cub, &cub->ceil);
			cub->flag[7] = 1;
		}
		else
		{
			printf("Error\nToo many parameters ceil color\n");
			cub->err = 1;
		}
	}	
}
