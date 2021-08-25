/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <lwiedijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/19 12:30:18 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/08/25 11:55:51 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <stdlib.h>

void	declare_map(t_maze *blueprint, t_port *port)
{
	int	i;

	i = 0;
	blueprint->map = (int **)malloc(sizeof(int *) * blueprint->map_y);
	if (!blueprint->map)
		ft_error(MALLOC_FAIL, port);
	while (i < blueprint->map_y)
	{
		blueprint->map[i] = (int *)malloc(sizeof(int) * blueprint->map_x[i]);
		if (!blueprint->map[i])
			ft_error(MALLOC_FAIL, port);
		i++;
	}
}

void	count_x(t_maze *blueprint, char *mapfile, int y, t_port *port)
{
	int	i;
	int	y_count;

	y_count = 0;
	i = blueprint->filepos;
	blueprint->map_x = (int *)malloc(sizeof(int) * y);
	if (!blueprint->map_x)
		ft_error(MALLOC_FAIL, port);
	while (y_count < y)
	{
		blueprint->map_x[y_count] = 0;
		while (mapfile[i] != '\n' && mapfile[i] != '\0')
		{
			blueprint->map_x[y_count]++;
			i++;
		}
		y_count++;
		i++;
	}
}

int	count_map_yx(t_maze *blueprint, char *mapfile, t_port *port)
{
	int	len;
	int	count_y;

	len = blueprint->filepos;
	count_y = 0;
	while (mapfile[len] == ' ' || mapfile[len] == '1' || mapfile[len] == '0'
		|| mapfile[len] == 'S'
		|| mapfile[len] == 'N' || mapfile[len] == 'W' || mapfile[len] == 'E')
	{
		len++;
		if (mapfile[len] == '\n'
			|| mapfile[len] == '\0')
		{
			count_y++;
			len++;
		}
	}
	check_map_existence(mapfile, count_y, len, port);
	blueprint->map_y = count_y;
	count_x(blueprint, mapfile, count_y, port);
	return (len);
}

void	parse_map(t_maze *blueprint, char *mapfile, t_port *port)
{
	int	pos_offset;

	pos_offset = count_map_yx(blueprint, mapfile, port);
	declare_map(blueprint, port);
	write_map(blueprint, mapfile, port);
	blueprint->filepos += (pos_offset - blueprint->filepos);
	while (mapfile[blueprint->filepos] == '\n'
		|| mapfile[blueprint->filepos] == ' ')
		blueprint->filepos++;
}
