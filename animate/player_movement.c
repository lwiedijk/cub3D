/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player_movement.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/12 09:43:25 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/05/12 10:05:11 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../mlx/mlx.h"
#include <math.h>

void	put_player(t_port *port, int x, int y, int color)
{
	int xi;
	int yi;
	int pos_y;
	int pos_x;

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
	y = y - 6;
	if (y < pos_y - 4)
	{
		draw_line(port->mlx, (x + 5), y, (x + cos(port->player->rotation) * 40), 
			(y + sin(port->player->rotation) * 40), 0xFFFFFF);
		//draw_line(port->mlx, 500, 220, 516, 245, 0xFFFFFF); 
	}
}

void	walk_player(t_port *port)
{
	double step;
	int newpos_x;
	int newpos_y;

	if (port->player->turndirection)
		port->player->rotation += (port->player->turndirection * port->player->rotation_speed);
	if (port->player->walkdirection)
	{
		step = (port->player->walkdirection * port->player->move_speed);
		newpos_y = port->player->pos_y + sin(port->player->rotation) * step;
		newpos_x = port->player->pos_x + cos(port->player->rotation) * step;
		if (!wall_hit(newpos_x, newpos_y, port))
		{
			port->player->pos_y = newpos_y;
			port->player->pos_x = newpos_x;
		}
	}
}

int	wall_hit(int x, int y, t_port *port)
{
	int wall_pos_x;
	int wall_pos_y;

	if (x < 0 || x > port->blueprint->screenres_x)
		return (1);
	if (y < 0 || x > port->blueprint->screenres_y)
		return (1);
	wall_pos_x = x / 20;
	wall_pos_y = y / 20;
	if (port->blueprint->map[wall_pos_y][wall_pos_x] > 0)
		return (1);
	return (0);
}




