/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player_sprites.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiranda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 12:24:57 by tmiranda          #+#    #+#             */
/*   Updated: 2021/04/07 12:28:15 by tmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_player_pos(char p, t_player *player)
{
	if (p == 'W')
	{
		(*player).dir_x = -1;
		(*player).plane_y = 0.66;
		player->fl++;
	}
	if (p == 'E')
	{
		(*player).dir_x = 1;
		(*player).plane_y = -0.66;
		player->fl++;
	}
	if (p == 'S')
	{
		(*player).dir_y = 1;
		(*player).plane_x = 0.66;
		player->fl++;
	}
	if (p == 'N')
	{
		(*player).dir_y = -1;
		(*player).plane_x = -0.66;
		player->fl++;
	}
}

int	parse_player_and_sprites(t_map *cub, t_player *player)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j] != '\0')
		{
			if (ft_strchr("NSEW", (*cub).map[i][j]))
			{
				set_player_pos((*cub).map[i][j], player);
				(*player).x = j + 0.5;
				(*player).y = i + 0.5;
				(*cub).map[i][j] = '0';
			}
			if ((*cub).map[i][j] == '2')
				k++;
			j++;
		}
		i++;
	}
	return (k);
}

void	parse_sprite(t_sprite *sprite, t_map *cub)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j] != '\0')
		{
			if ((*cub).map[i][j] == '2')
			{
				sprite[k].x = j + 0.5;
				sprite[k].y = i + 0.5;
				sprite[k].dist = 0;
				k++;
			}
			j++;
		}
		i++;
	}
}
