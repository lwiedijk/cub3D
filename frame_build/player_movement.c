/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player_movement.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/12 09:43:25 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/08/25 11:49:15 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <math.h>

void	set_player_rotation(t_port *port, t_maze *p)
{
	if (p->player_or == 'N')
		port->player->rotation = M_PI * -0.5;
	if (p->player_or == 'E')
		port->player->rotation = M_PI / 0.5;
	if (p->player_or == 'S')
		port->player->rotation = M_PI / 2;
	if (p->player_or == 'W')
		port->player->rotation = M_PI;
	normalize_ray_angle(&port->player->rotation);
}

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
				set_player_rotation(port, port->blueprint);
				port->player->pos_x = ((x * TILE_SIZE) + (TILE_SIZE / 2));
				port->player->pos_y = ((y * TILE_SIZE) + (TILE_SIZE / 2));
				port->blueprint->map[y][x] = 0;
			}
			x++;
		}
		y++;
	}
}

void	strafe_player(t_port *port, int direction)
{
	float		step;
	float		newpos_x;
	float		newpos_y;

	step = (direction * port->player->move_speed);
	newpos_y = port->player->pos_y
		+ (sin(port->player->rotation - M_PI_2)) * step;
	newpos_x = port->player->pos_x
		+ (cos(port->player->rotation - M_PI_2)) * step;
	if (!wall_hit(newpos_x, newpos_y, port))
	{
		port->player->pos_y = newpos_y;
		port->player->pos_x = newpos_x;
	}
}

void	walk_player(t_port *port, int direction)
{
	float		step;
	float		newpos_x;
	float		newpos_y;

	step = (direction * port->player->move_speed);
	newpos_y = port->player->pos_y + sin(port->player->rotation) * step;
	newpos_x = port->player->pos_x + cos(port->player->rotation) * step;
	if (!wall_hit(newpos_x, newpos_y, port))
	{
		port->player->pos_y = newpos_y;
		port->player->pos_x = newpos_x;
	}
}

void	move_player(t_port *port)
{
	if (port->player->turndirection_r)
		port->player->rotation += (port->player->turndirection_r
				* port->player->rotation_speed);
	if (port->player->turndirection_l)
		port->player->rotation += (port->player->turndirection_l
				* port->player->rotation_speed);
	if (port->player->forward)
		walk_player(port, port->player->forward);
	if (port->player->backward)
		walk_player(port, port->player->backward);
	if (port->player->strafe_r)
		strafe_player(port, port->player->strafe_r);
	if (port->player->strafe_l)
		strafe_player(port, port->player->strafe_l);
}
