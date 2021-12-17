/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiranda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 11:26:38 by tmiranda          #+#    #+#             */
/*   Updated: 2021/04/07 11:32:10 by tmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	keypress(int keycode, t_key *key)
{	
	if (keycode == 2)
		key->key_d = 1;
	if (keycode == 0)
		key->key_a = 1;
	if (keycode == 13)
		key->key_w = 1;
	if (keycode == 1)
		key->key_s = 1;
	if (keycode == 124)
		key->key_r = 1;
	if (keycode == 123)
		key->key_l = 1;
	if (keycode == 53)
		key->key_esc = 1;
	return (1);
}

int	keyrelease(int keycode, t_key *key)
{
	if (keycode == 2)
		key->key_d = 0;
	if (keycode == 0)
		key->key_a = 0;
	if (keycode == 13)
		key->key_w = 0;
	if (keycode == 1)
		key->key_s = 0;
	if (keycode == 124)
		key->key_r = 0;
	if (keycode == 123)
		key->key_l = 0;
	return (1);
}

void	key_init(t_key *key)
{
	key->key_a = 0;
	key->key_d = 0;
	key->key_w = 0;
	key->key_s = 0;
	key->key_r = 0;
	key->key_l = 0;
	key->key_esc = 0;
}

int	exit_hook(void)
{
	exit (0);
}
