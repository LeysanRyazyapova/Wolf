/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsetostruct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiranda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 12:30:01 by tmiranda          #+#    #+#             */
/*   Updated: 2021/04/07 12:44:53 by tmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_texture(char **dst, char *line, char *str, int *fl)
{
	int	n;
	int	i;
	int	j;

	n = ft_strlen(line);
	j = 0;
	if (line[0] == str[0] && line[1] == str[1] && line[2] == ' ')
	{
		if (*fl == 0)
		{
			i = 2;
			while (line[i] == ' ')
				i++;
			*dst = ft_substr(line, i, n);
			*fl = 1;
		}
		else
			return (0);
	}
	return (1);
}

int	parse_textureS(char **dst, char *line, char *str, int *fl)
{
	int	n;
	int	i;
	int	j;

	n = ft_strlen(line);
	j = 0;
	if (line[0] == str[0] && line[1] == str[1])
	{
		if (*fl == 0)
		{
			i = 2;
			while (line[i] == ' ')
				i++;
			*dst = ft_substr(line, i, n);
			*fl = 1;
		}
		else
			return (0);
	}
	return (1);
}

void	parse_resolution(char *line, t_map *cub)
{
	int	i;

	if (line[0] == 'R' && line[1] == ' ')
	{	
		if (cub->flag[0] == 0)
		{
			i = 1;
			while (line[i] == ' ')
				i++;
			if (!get_num(line, &i, &cub->w, ' '))
				cub->err = 1;
			while (line[i] == ' ')
				i++;
			if (!get_num(line, &i, &cub->h, '\0'))
				cub->err = 1;
			cub->flag[0] = 1;
		}
		else
			cub->err = 1;
	}	
}

void	parsetostruct(char *line, t_map *cub)
{
	if (ft_strchr("RNSWEFC", line[0]))
	{
		parse_resolution(line, cub);
		if (!parse_texture(&cub->no, line, "NO", &cub->flag[1]))
			cub->err = 1;
		if (!parse_texture(&cub->so, line, "SO", &cub->flag[2]))
			cub->err = 1;
		if (!parse_texture(&cub->we, line, "WE", &cub->flag[3]))
			cub->err = 1;
		if (!parse_texture(&cub->ea, line, "EA", &cub->flag[4]))
			cub->err = 1;
		if (!parse_textureS(&cub->s, line, "S ", &cub->flag[5]))
			cub->err = 1;
		parse_F(line, cub);
		parse_C(line, cub);
	}
	else
		cub->err = 1;
	free(line);
	line = NULL;
}
