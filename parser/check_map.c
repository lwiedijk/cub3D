/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/21 15:18:56 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/08/24 15:45:51 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>

int	check_opening_in_map(t_port *port, int **map, int y, int x)
{
	if ((y - 1) < 0)
		ft_error(INVALID_MAP, port);
	else if ((x - 1) < 0)
		ft_error(INVALID_MAP, port);
	else if (map[y][x - 1] == ' ')
		ft_error(INVALID_MAP, port);
	else if ((x + 1) >= port->blueprint->map_x[y] || map[y][x + 1] == ' ')
		ft_error(INVALID_MAP, port);
	else if (x >= port->blueprint->map_x[y - 1] || map[y - 1][x] == ' ')
		ft_error(INVALID_MAP, port);
	else if ((y + 1) >= port->blueprint->map_y
		|| x >= port->blueprint->map_x[y + 1] || map[y + 1][x] == ' ')
		ft_error(INVALID_MAP, port);
	return (0);
}

void	check_map_existence(char *mapfile, int count_y, int len, t_port *port)
{
	if (!count_y)
	{
		if (mapfile[len] != ' ' && mapfile[len] != '\n' && mapfile[len] != '\0')
			ft_error(INCORRECT_CUB_FILE, port);
		ft_error(MISSING_MAP, port);
	}
}

void	check_map(int **map, t_maze blueprint, t_port *port)
{
	int	x;
	int	y;

	y = 0;
	if (!blueprint.player_or)
		ft_error(MISSING_PLAYER, port);
	while (y < blueprint.map_y)
	{
		x = 0;
		while (x < blueprint.map_x[y])
		{
			if (map[y][x] == 0 || map[y][x] == 112)
				check_opening_in_map(port, map, y, x);
			x++;
		}
		y++;
	}
}

int	loop_through_map(t_port *port, char mapfile, int x, int y)
{
	if (mapfile >= '0' && mapfile <= '1')
	{
		port->blueprint->map[y][x] = (int)mapfile - '0';
		x++;
	}
	else if (mapfile == 'N' || mapfile
		== 'E' || mapfile == 'W' || mapfile == 'S')
	{
		if (port->blueprint->player_or)
			ft_error(TOO_MANY_PLAYERS, port);
		port->blueprint->player_or = mapfile;
		port->blueprint->map[y][x] = 'p';
		x++;
	}
	else if (mapfile == ' ')
	{
		port->blueprint->map[y][x] = ' ';
		x++;
	}
	return (x);
}

void	write_map(t_maze *blueprint, char *mapfile, t_port *port)
{
	int	i;
	int	y;
	int	x;

	i = blueprint->filepos;
	y = 0;
	while (y < blueprint->map_y)
	{
		x = 0;
		while (x < blueprint->map_x[y])
		{
			x = loop_through_map(port, mapfile[i], x, y);
			i++;
		}
		if (mapfile[i] == '\n')
			i++;
		y++;
	}
	check_map(blueprint->map, *blueprint, port);
}
