/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <lwiedijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/19 12:30:18 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/07/09 16:28:05 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	check_opening_in_map(t_maze blueprint, int **map, int y, int x)
{
	if ((y - 1) < 0)
		ft_error(INVALID_MAP);
	if ((x - 1) < 0)
		ft_error(INVALID_MAP);
	else if (map[y][x - 1] == ' ')
		ft_error(INVALID_MAP);
	else if (x + 1 >= blueprint.map_x[y])
		ft_error(INVALID_MAP);
	else if (map[y][x + 1] == ' ')
		ft_error(INVALID_MAP);
	else if (map[y - 1][x] == ' ')
		ft_error(INVALID_MAP);
	else if (y + 1 >= blueprint.map_y)
		ft_error(INVALID_MAP);
	else if (map[y + 1][x] == ' ')
		ft_error(INVALID_MAP);
	return (0);
}

void	check_map(int **map, t_maze blueprint)
{
	int	x;
	int	y;

	y = 0;
	if (!blueprint.player_or)
		ft_error(INCORRECT_CUB_FILE);
	while (y < blueprint.map_y)
	{
		x = 0;
		while(x < blueprint.map_x[y])
		{
			if (map[y][x] == 0 || map[y][x] == 112)
				check_opening_in_map(blueprint, map, y, x);
			x++;
		}
		y++;
	}
}

void	write_map(t_maze *blueprint, char *mapfile)
{
	int	i;
	int y;
	int x;

	i = blueprint->filepos;
	y = 0;
	while (y < blueprint->map_y)
	{
		x = 0;
		while (x < blueprint->map_x[y])
		{
			if (mapfile[i] >= '0' && mapfile[i] <= '1')
			{
				blueprint->map[y][x] = (int)mapfile[i] - '0';
				x++;
			}
			else if (mapfile[i] == 'N' || mapfile[i]
			== 'E' || mapfile[i] == 'W' || mapfile[i] == 'S')
			{
				if (blueprint->player_or)
					ft_error(INCORRECT_CUB_FILE);
				blueprint->player_or = mapfile[i];
				blueprint->map[y][x] = 'p';
				x++;
			}
			else if (mapfile[i] == ' ')
			{
				blueprint->map[y][x] = ' ';
				x++;
			}
			i++;
		}
		if (mapfile[i] == '\n')
			i++;
		y++;
	}
	check_map(blueprint->map, *blueprint);
}

void	declare_map(t_maze *blueprint)
{
	int i;

	i = 0;
	blueprint->map = (int **)malloc(sizeof(int *) * blueprint->map_y);
	if (!blueprint->map)
		ft_error(MALLOC_FAIL);
	while (i < blueprint->map_y)
	{
		blueprint->map[i] = (int *)malloc(sizeof(int) * blueprint->map_x[i]);
		if (!blueprint->map[i])
			ft_error(MALLOC_FAIL);
		i++;
	}
}

void	count_x(t_maze *blueprint, char *mapfile, int y)
{
	int i;
	int y_count;
	
	y_count = 0;
	i = blueprint->filepos;
	blueprint->map_x = (int *)malloc(sizeof(int) * y);
	if (!blueprint->map_x)
		ft_error(MALLOC_FAIL);
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

int	count_map_yx(t_maze *blueprint, char *mapfile)
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
		if (mapfile[len] == '\n')
		{
			count_y++;
			len++;
		}
	}
	if (mapfile[len] != '\n')
		ft_error(INVALID_MAP);
	if (!count_y)
		ft_error(INVALID_MAP);
	blueprint->map_y = count_y;
	count_x(blueprint, mapfile, count_y);
	return (len);
}

void	parse_map(t_maze *blueprint, char *mapfile)
{
	int pos_offset;

	pos_offset = count_map_yx(blueprint, mapfile);
	declare_map(blueprint);
	write_map(blueprint, mapfile);
	blueprint->filepos += (pos_offset - blueprint->filepos);
	while (mapfile[blueprint->filepos] == ' ')
		blueprint->filepos++;
}