/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_massive.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiranda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 09:31:26 by tmiranda          #+#    #+#             */
/*   Updated: 2021/04/07 13:43:34 by tmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
int	check_not_space(char *str1, char *str2, char *comp)
{
	int	n;
	int	m;
	int	j;

	n = ft_strlen(str1);
	m = ft_strlen(str2);
	j = 1;
	while (comp[j] != '\0')
	{
		if (ft_strchr("NSWE02", comp[j]))
		{
			if (j > n || j > m)
				return (0);
			else
			{
				if (str1[j] == ' ' || comp[j - 1] == ' ' || comp[j + 1] == ' '
					|| str2[j] == ' ' || comp[j + 1] == '\0'
					|| str2[j] == '\0' || str1[j] == '\0')
					return (0);
			}
		}
		j++;
	}
	return (1);
}

void	check_first_element(t_map *cub)
{
	int	i;

	i = 0;
	while (cub->map[i])
	{
		if (cub->map[i][0] != ' ' && cub->map[i][0] != '1')
			cub->err = 1;
		i++;
	}
}

int	check_first_past(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ' && str[i] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	check_massive(t_map *cub)
{
	int	i;

	i = 0;
	if (!check_first_past(cub->map[i]))
	{
		cub->err = 1;
		return (0);
	}
	i++;
	while (i < cub->max_y - 1)
	{
		if (!check_not_space(cub->map[i - 1], cub->map[i + 1], cub->map[i]))
		{
			cub->err = 1;
			return (0);
		}
		i++;
	}
	if (!check_first_past(cub->map[i]))
	{
		cub->err = 1;
		return (0);
	}
	return (1);
}

int	valid_map(t_map *cub)
{
	if (!check_all(cub->map))
	{
		cub->err = 1;
		return (0);
	}	
	if (cub->max_x < 3 || cub->max_y < 3)
	{
		cub->err = 1;
		return (0);
	}
	if (!check_massive(cub))
	{
		cub->err = 1;
		return (0);
	}	
	check_first_element(cub);
	return (1);
}
