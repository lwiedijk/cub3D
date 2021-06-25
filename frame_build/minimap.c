/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/16 11:29:35 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/06/25 15:07:22 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../mlx/mlx.h"
#include <math.h>

void	draw_mini_player(t_port *port, float x, float y, int color)
{
	float	xi;
	float	yi;
	float	pos_y;
	float	pos_x;

	pos_y = (y - 3);
	xi = (x + 3);
	yi = (y + 3);
	draw_line(port->mlx, port->player, (x + cos(port->player->rotation) * (0.15
				* TILE_SIZE)), (y + sin(port->player->rotation) * (0.15
				* TILE_SIZE)));
	while (pos_y < yi)
	{
		pos_x = (x - 3);
		while (pos_x < xi)
		{
			my_mlx_pixel_put(port->mlx, pos_x, pos_y, color);
			pos_x++;
		}
		pos_y++;
	}
}

void	put_square(t_port *port, float x, float y, int color)
{
	float	xi;
	float	pos_y;
	float	pos_x;

	pos_y = y + (SCALE * TILE_SIZE);
	pos_x = x + (SCALE * TILE_SIZE);
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
}

void	draw_mini_map(t_port *port)
{
	int		x;
	int		y;
	float	step;
	float	jump;

	y = 0;
	jump = 0;
	while (y < port->blueprint->map_y)
	{
		x = 0;
		step = 0;
		while (x < port->blueprint->map_x[y])
		{
			if (port->blueprint->map[y][x] == 1)
			{
				put_square(port, step, jump, 0x00FF00);
				step += port->blueprint->step_size;
			}
			if (port->blueprint->map[y][x] == 0)
				step += port->blueprint->step_size;
			x++;
		}
		jump += port->blueprint->step_size;
		y++;
	}
}

void	draw_line(t_mlx *mlx, t_player *player, float end_x, float end_y)
{
	float	delta_x;
	float	delta_y;
	int		pixel_count;
	float	pixel_x;
	float	pixel_y;

	delta_x = end_x - (SCALE * player->pos_x);
	delta_y = end_y - (SCALE * player->pos_y);
	pixel_count = sqrt((delta_x * delta_x) + (delta_y * delta_y));
	delta_x /= pixel_count;
	delta_y /= pixel_count;
	pixel_x = (SCALE * player->pos_x);
	pixel_y = (SCALE * player->pos_y);
	while (pixel_count)
	{
		my_mlx_pixel_put(mlx, pixel_x, pixel_y, 0x0000FF);
		pixel_x += delta_x;
		pixel_y += delta_y;
		--pixel_count;
	}
}
