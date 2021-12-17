/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiranda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 19:54:05 by tmiranda          #+#    #+#             */
/*   Updated: 2021/04/08 07:04:21 by tmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define RAD 0.017453292519943
# define U_DIV 1
# define V_DIV 1
# define V_MOVE 0.0

# include "mlx.h"
# include <math.h>
# include "libft.h"
# include "get_next_line.h"
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct s_map
{
	int		w;
	int		h;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*s;
	int		floor;
	int		ceil;
	char	**map;
	int		flag[8];
	int		max_x;
	int		max_y;
	int		err;
}	t_map;
typedef struct s_key
{
	int	key_w;
	int	key_s;
	int	key_a;
	int	key_d;
	int	key_r;
	int	key_l;
	int	key_esc;
}	t_key;
typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		length;
	int		endian;
	int		width;
	int		height;
}	t_data;
typedef struct s_player
{
	float	x;
	float	y;
	float	dir_x;
	float	dir_y;
	float	plane_x;
	float	plane_y;
	int		fl;
}	t_player;
typedef struct s_camera
{
	float	camera_x;
	float	ray_x;
	float	ray_y;
	float	tile_x;
	float	tile_y;
	float	step_x;
	float	step_y;
	float	xintercept;
	float	yintercept;
	int		mapX;
	int		mapY;
	int		s;
	float	dist;
}	t_camera;
typedef struct s_text
{
	t_data	noth;
	t_data	south;
	t_data	west;
	t_data	east;
	t_data	sp;
}	t_text;
typedef struct s_draw
{
	float	wall_x;
	int		tex_x;
	int		wall_h;
	int		start;
	int		end;
	float	step;
	float	tex_pos;	
	t_data	current;
}	t_draw;
typedef struct s_sprite
{
	float	x;
	float	y;
	float	dist;
}	t_sprite;
typedef struct s_drsp
{
	float	spr_x;
	float	spr_y;
	float	inv_det;
	float	tr_x;
	float	tr_y;
	int		spr_scr_x;
	int		v_movescreen;
	int		spr_h;
	int		start_y;
	int		end_y;
	int		start_x;
	int		end_x;
	int		spr_w;
	int		h;
	int		w;
}	t_drsp;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	int			k;
	float		*z_buffer;
	t_data		data;
	t_map		cub;
	t_player	pl;
	t_camera	cam;
	t_draw		draw;
	t_text		text;
	t_sprite	*spr;
	t_drsp		drsp;
	t_key		key;
	int			save;
}	t_vars;
int					check_end(char *str);
int					keypress(int keycode, t_key *key);
int					keyrelease(int keycode, t_key *key);
int					check_param_count(t_map *cub);
int					check_all(char **comp);
void				calc_dist_sprite(int k, t_sprite *spr, t_player *pl);
void				check_screensize(t_map *cub);
void				key_init(t_key *key);
void				parse_map(t_map *cub, int fd);
int					check_massive(t_map *cub);
void				parse_F(char *line, t_map *cub);
void				parse_C(char *line, t_map *cub);
void				initialisation(t_vars *vars);
void				parsetostruct(char *line, t_map *cub);
int					get_num(char *line, int *i, int *num, char c);
void				check_texture(t_map *cub);
int					check_read_texture(char *str, t_data *text, t_vars *vars);
int					check_digit(char *str);
unsigned long long	ft_atoll(const char *str);
int					parse_player_and_sprites(t_map *cub, t_player *player);
int					valid_map(t_map *cub);
void				parse_sprite(t_sprite *sprite, t_map *cub);
int					squere_size(t_map *cub, int res);
void				make_mini_map(t_map *cub, t_data *data, t_player *player);
void				make_empty_map(t_map *cub, t_data *data, t_player *player);
void				my_clear_window(t_data *data, t_map *cub);
void				my_mlx_pixel_put(t_data *data, int x, int y, int color);
unsigned int		my_mlx_pixel_take(t_data *data, int x, int y);
void				cast_ray(t_vars *vars);
void				rotate_left(t_player *pl);
void				rotate_right(t_player *pl);
int					walking(t_vars *vars);
void				draw_sprite(t_vars *vars);
void				draw_center(t_vars *vars, int x, int y);
void				draw(t_vars *vars, int x);
int					exit_hook(void);
int					make_bmp(t_vars *vars);

#endif
