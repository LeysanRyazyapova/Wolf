/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiranda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 11:05:18 by tmiranda          #+#    #+#             */
/*   Updated: 2021/04/04 16:30:15 by tmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "cub3d.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void	init_structs(t_map *cub, t_player *player)
{
	cub->h = 0;
	cub->w = 0;
	cub->no = 0;
	cub->so = 0;
	cub->we = 0;
	cub->ea = 0;
	cub->flag[0] = 0;
	cub->flag[1] = 0;
	cub->flag[2] = 0;
	cub->flag[3] = 0;
	cub->flag[4] = 0;
	cub->flag[5] = 0;
	cub->flag[6] = 0;
	cub->flag[7] = 0;
	cub->max_x = 0;
	cub->max_y = 0;
	cub->err = 0;
	player->x = 0.0001;
	player->y = 0.0001;
	player->dir_x = 0.0001;
	player->dir_y = 0.0001;
	player->plane_x = 0.0001;
	player->plane_y = 0.0001;
	player->fl = 0;
}

void	init_texture(t_vars *vars, t_text *text, t_map *cub)
{
	if (vars->cub.err == 0)
	{
		check_read_texture(cub->no, &text->noth, vars);
		check_read_texture(cub->so, &text->south, vars);
		check_read_texture(cub->ea, &text->east, vars);
		check_read_texture(cub->we, &text->west, vars);
		check_read_texture(cub->s, &text->sp, vars);
	}
}

void	init(t_vars *vars, int fd)
{
	init_structs(&vars->cub, &vars->pl);
	parse_map(&vars->cub, fd);
	vars->k = parse_player_and_sprites(&vars->cub, &vars->pl);
	vars->spr = (t_sprite *)malloc(sizeof(t_sprite) * vars->k);
	parse_sprite(vars->spr, &vars->cub);
	vars->save = 0;
	vars->mlx = mlx_init();
	if (valid_map(&vars->cub))
	{
		init_texture(vars, &vars->text, &vars->cub);
	}
	else
		vars->cub.err = 1;
	if (vars->pl.fl != 1)
		vars->cub.err = 1;
}

void	play(t_vars *vars)
{
	initialisation(vars);
	key_init(&vars->key);
	if (vars->cub.err != 1)
	{
		mlx_hook(vars->win, 2, 0, &keypress, &vars->key);
		mlx_hook(vars->win, 3, 0, &keyrelease, &vars->key);
		mlx_hook(vars->win, 17, 1, &exit_hook, &vars->key);
		mlx_loop_hook(vars->mlx, walking, vars);
		mlx_loop(&vars->mlx);
	}
	else
		printf("Error\nMap isn't valid");
}

int	main(int argc, char **argv)
{
	int		fd;
	t_vars	vars;

	if (argc == 2 || argc == 3)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0 || read(fd, NULL, 0) == -1 || check_end(argv[1]))
		{
			printf("Error\nCan't open file");
			return (0);
		}
		init(&vars, fd);
		if (argc == 2)
			play(&vars);
		else if (!ft_strncmp("--save", argv[2], 7))
			make_bmp(&vars);
		else
			printf("Error\nNot valid \"--save\"");
		close(fd);
	}
	else
		printf("Error\nPlease, add map to arg");
	return (0);
}
