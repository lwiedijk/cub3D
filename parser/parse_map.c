/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <lwiedijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/19 12:30:18 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/04/13 18:49:22 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>

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
			if (mapfile[i] >= '0' && mapfile[i] <= '2')
			{
				blueprint->map[y][x] = (int)mapfile[i] - '0';
				x++;
			}
			else if (mapfile[i] == 'N' || mapfile[i]
			== 'E' || mapfile[i] == 'W' || mapfile[i] == 'S')
			{
				blueprint->map[y][x] = 8;
				x++;
			}
			else if (mapfile[i] == ' ')
			{
				blueprint->map[y][x] = 0;
				x++;
			}
			i++;
		}
		if (mapfile[i] == '\n')
			i++;
		y++;
	}
}

void	declare_map(t_maze *blueprint)
{
	int i;

	i = 0;
	blueprint->map = (int **)malloc(sizeof(int *) * blueprint->map_y);
	if (!blueprint->map)
		ft_error(2);
	while (i < blueprint->map_y)
	{
		blueprint->map[i] = (int *)malloc(sizeof(int) * blueprint->map_x[i]);
		if (!blueprint->map[i])
			ft_error(2);
		i++;
	}
	//free(blueprint->map_x);
}

void	count_x(t_maze *blueprint, char *mapfile, int y)
{
	int i;
	int y_count;
	
	y_count = 0;
	i = blueprint->filepos;
	blueprint->map_x = (int *)malloc(sizeof(int) * y);
	if (!blueprint->map_x)
		ft_error(2);
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

int	checkmap_and_count_y(t_maze *blueprint, char *mapfile)
{
	int	len;
	int	count;

	len = blueprint->filepos;
	count = 0;
	while (mapfile[len] == ' ' || mapfile[len] == '1' || mapfile[len] == '0'
		|| mapfile[len] == '2' || mapfile[len] == 'S'
		|| mapfile[len] == 'N' || mapfile[len] == 'W' || mapfile[len] == 'E')
	{
		len++;
		if (mapfile[len] == '\n')
		{
			count++;
			len++;
		}
	}
	if (!count)
		ft_error(1);
	blueprint->map_y = count;
	count_x(blueprint, mapfile, count);
	return (len);
}

void	parse_map(t_maze *blueprint, char *mapfile)
{
	int len;

	len = checkmap_and_count_y(blueprint, mapfile);
	declare_map(blueprint);
	write_map(blueprint, mapfile);
	blueprint->filepos += (len - blueprint->filepos);
	while (mapfile[blueprint->filepos] == ' ')
		blueprint->filepos++;
}