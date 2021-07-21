/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/16 11:29:35 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/07/21 15:03:56 by lwiedijk      ########   odam.nl         */
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
	draw_line(port->mlx, port->player, (x + cos(port->player->rotation) * (SCALE
				* TILE_SIZE)), (y + sin(port->player->rotation) * (SCALE
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

void	draw_mini_map(t_port *port, t_maze *blueprint, float jump)
{
	int		x;
	int		y;
	float	step;

	y = 0;
	while (y < blueprint->map_y)
	{
		x = 0;
		step = 0;
		while (x < blueprint->map_x[y])
		{
			if (blueprint->map[y][x] == 1)
			{
				put_square(port, step, jump, 0x00FF00);
				step += blueprint->step_size;
			}
			if (blueprint->map[y][x] == 0
				|| blueprint->map[y][x] == ' ')
				step += blueprint->step_size;
			x++;
		}
		jump += blueprint->step_size;
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
