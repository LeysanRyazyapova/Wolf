/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiranda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 20:12:38 by tmiranda          #+#    #+#             */
/*   Updated: 2021/04/08 07:07:20 by tmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "../Libft/libft.h"

char	*ft_strcpy(char *src, char *dst)
{
	int	i;

	i = 0;
	if (dst == 0 || src == 0)
		return (0);
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_checkrem(char **remainder, char **line)
{
	char	*ptr;

	ptr = NULL;
	if (*remainder)
	{
		ptr = ft_strchr(*remainder, '\n');
		if (ptr)
		{
			*ptr = '\0';
			*line = ft_strdup(*remainder);
			ptr++;
			ft_strcpy(ptr, *remainder);
		}
		else
		{
			*line = ft_strdup(*remainder);
			free(*remainder);
			*remainder = NULL;
		}
	}
	else
		*line = ft_strdup("");
	return (ptr);
}

static int	ret_val(char *ptr)
{
	if (ptr)
		return (1);
	else
		return (0);
}

int	get_next_line(int fd, char **line)
{
	int			ret;
	char		buf[10001];
	static char	*remainder;
	char		*ptr;
	char		*tmp;

	if (!(line) || fd < 0 || read(fd, 0, 0) < 0)
		return (-1);
	ptr = ft_checkrem(&remainder, line);
	ret = read(fd, buf, 10000);
	while (!ptr && ret)
	{
		buf[ret] = '\0';
		ptr = ft_strchr(buf, '\n');
		if (ptr)
		{
			*ptr = '\0';
			remainder = ft_strdup(++ptr);
		}
		tmp = *line;
		*line = ft_strjoin(*line, buf);
		free(tmp);
	}
	return (ret_val(ptr));
}
