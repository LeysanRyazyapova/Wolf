/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiranda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 13:59:07 by tmiranda          #+#    #+#             */
/*   Updated: 2021/04/07 12:24:09 by tmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	max_xy(t_map *cub)
{
	int	i;
	int	n;
	int	m;

	m = 0;
	i = 0;
	while (cub->map[i])
	{
		n = ft_strlen(cub->map[i]);
		if (m < n)
			m = n;
		i++;
	}
	cub->max_x = m;
	cub->max_y = i;
}

char	**make_map(t_list **head, int size)
{
	char	**map;
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = *head;
	map = (char **)malloc(sizeof(char *) * (size + 1));
	while (tmp)
	{
		map[i] = ft_strdup(tmp->content);
		tmp = tmp->next;
		i++;
	}
	map[i] = NULL;
	return (map);
}

void	parse_massive(char *line, int *fl, t_list **head, t_map *cub)
{
	if (line[0] == '\0')
	{
		if (*fl == 1)
			cub->err = 1;
		free(line);
		line = NULL;
	}
	else
	{
		ft_lstadd_back(head, ft_lstnew(line));
		*fl = 1;
	}
}

void	parse_map(t_map *cub, int fd)
{
	char	*line;
	t_list	*head;
	int		fl;

	fl = 0;
	head = NULL;
	while (get_next_line(fd, &line))
	{
		if (!check_param_count(cub))
		{
			if (line[0] != '\0')
				parsetostruct(line, cub);
			else
				free(line);
			line = NULL;
		}
		else
			parse_massive(line, &fl, &head, cub);
	}
	ft_lstadd_back(&head, ft_lstnew(line));
	(*cub).map = make_map(&head, ft_lstsize(head));
	ft_lstclear(&head, free);
	max_xy(cub);
}
