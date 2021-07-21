/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/21 15:18:56 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/07/21 15:21:12 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>

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
		while (x < blueprint.map_x[y])
		{
			if (map[y][x] == 0 || map[y][x] == 112)
				check_opening_in_map(blueprint, map, y, x);
			x++;
		}
		y++;
	}
}