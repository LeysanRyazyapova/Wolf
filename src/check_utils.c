/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiranda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 09:08:09 by tmiranda          #+#    #+#             */
/*   Updated: 2021/04/08 07:34:01 by tmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned long long	ft_atoll(const char *str)
{
	int					i;
	unsigned long long	d;
	int					z;

	z = 1;
	i = 0;
	d = 0;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		d = str[i] - '0' + d * 10;
		i++;
	}
	return (d * z);
}

int	check_all(char **comp)
{
	int	i;
	int	j;

	i = 0;
	while (comp[i])
	{
		j = 0;
		while (comp[i][j] != '\0')
		{
			if (comp[i][j] != '0' && comp[i][j] != '1' && comp[i][j] != '2'
			&& comp[i][j] != ' ')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] > '9' || str[i] < '0')
		{
			printf("Error\nWrong number\n");
			return (0);
		}
		i++;
	}
	if (i == 0)
	{
		printf("Error\nWrong number\n");
		return (0);
	}
	return (1);
}

int	get_num(char *line, int *i, int *num, char c)
{
	char				*str;
	int					j;
	unsigned long long	tmp;

	j = *i;
	while (line[*i] != c && line[*i] != '\0')
		(*i)++;
	str = ft_substr(line, j, *i - j);
	if (check_digit(str))
	{
		tmp = ft_atoll(str);
		if (tmp > INT_MAX)
			tmp = INT_MAX;
		*num = (int)tmp;
		free(str);
		return (1);
	}
	else
	{
		free(str);
		return (0);
	}
}

int	check_read_texture(char *str, t_data *text, t_vars *vars)
{
	text->img = mlx_xpm_file_to_image(vars->mlx, str,
			&text->width, &text->height);
	if (text->img == NULL)
	{
		vars->cub.err = 1;
		return (0);
	}
	text->addr = mlx_get_data_addr(text->img, &text->bpp,
			&text->length, &text->endian);
	return (1);
}
