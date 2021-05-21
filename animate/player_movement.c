/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player_movement.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/12 09:43:25 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/05/20 17:22:43 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../mlx/mlx.h"
#include <math.h>

void	set_player(t_port *port)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < port->blueprint->map_y)
	{
		x = 0;
		while (x < port->blueprint->map_x[y])
		{
			if (port->blueprint->map[y][x] == 'p')
			{
				port->player->pos_x = (x * port->blueprint->tile_size);
				port->player->pos_y = (y * port->blueprint->tile_size);
				port->blueprint->map[y][x] = 0;
			}
			x++;
		}
		y++;
	}
}

void	draw_player(t_port *port, int x, int y, int color)
{
	int	xi;
	int	yi;
	int	pos_y;
	int	pos_x;

	pos_y = y + 10;
	pos_x = x + 10;
	while (y < pos_y)
	{
		xi = x;
		while (xi < pos_x)
		{
			my_mlx_pixel_put(port->mlx, xi, y, color);
			xi++;
		}
		y++;
	}
	y = y - 10;
	if (y < pos_y)
	{
		draw_line(port->mlx, x, y, (x + cos(port->player->rotation) * 40),
			(y + sin(port->player->rotation) * 40), 0xFFFFFF);
	}
}

void	walk_player(t_port *port)
{
	double	step;
	int		newpos_x;
	int		newpos_y;
	int		wall_content;

	if (port->player->turndirection)
		port->player->rotation += (port->player->turndirection
				* port->player->rotation_speed);
	if (port->player->walkdirection)
	{
		step = (port->player->walkdirection * port->player->move_speed);
		newpos_y = port->player->pos_y + sin(port->player->rotation) * step;
		newpos_x = port->player->pos_x + cos(port->player->rotation) * step;
		if (!wall_hit(newpos_x, newpos_y, port, &wall_content))
		{
			port->player->pos_y = newpos_y;
			port->player->pos_x = newpos_x;
		}
	}
}

int	wall_hit(float x, float y, t_port *port, int *wall_content)
{
	int	wall_pos_x;
	int	wall_pos_y;

	if (x < 0 || x > port->blueprint->screenres_x)
		return (1);
	if (y < 0 || y > port->blueprint->screenres_y)
		return (1);
	wall_pos_x = floor(x / port->blueprint->tile_size);
	wall_pos_y = floor(y / port->blueprint->tile_size);
	if (wall_pos_y > (port->blueprint->map_y - 1))
		return (1);
	if (wall_pos_x > (port->blueprint->map_x[wall_pos_y]))
		return (1);
	if (port->blueprint->map[wall_pos_y][wall_pos_x] > 0)
	{
		*wall_content = port->blueprint->map[wall_pos_y][wall_pos_x];
		return (1);
	}
	return (0);
}
