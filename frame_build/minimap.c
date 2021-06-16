/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/16 11:29:35 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/06/16 11:36:28 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../mlx/mlx.h"
#include <math.h>

void	draw_player(t_port *port, int x, int y, int color)
{
	int	xi;
	int	yi;
	int	pos_y;
	int	pos_x;

	//pos_y = (y - 5);
	//xi = (x + 5);
	//yi = (y + 5);
	//while (pos_y < yi)
	//{
	//	pos_x = (x - 5);
	//	while (pos_x < xi)
	//	{
	//		my_mlx_pixel_put(port->mlx, pos_x, pos_y, color);
	//		pos_x++;
	//	}
	//	pos_y++;
	//}
	draw_line(port->mlx, x, y, (x + cos(port->player->rotation) * (SCALE * TILE_SIZE)),
		(y + sin(port->player->rotation) * (SCALE * TILE_SIZE)), 0xFFFFFF);
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


void	draw_2d_map(t_port *port)
{
	int	x;
	int	y;
	float	step;
	float	jump;
	float	jump_size;
	float	step_size;

	y = 0;
	jump = 0;
	jump_size = (SCALE * TILE_SIZE);
	step_size = (SCALE * TILE_SIZE);

	while(y < port->blueprint->map_y)
	{
		x = 0;
		step = 0;
		while (x < port->blueprint->map_x[y])
		{
			if (port->blueprint->map[y][x] > 0 && port->blueprint->map[y][x] < 2)
			{
				put_square(port, step, jump, 0x00FF00);
				step += step_size;
			}
			if (port->blueprint->map[y][x] == 2)
			{
				put_square(port, step, jump, 0x0000FF);
				step += step_size;
			}
			if (port->blueprint->map[y][x] == 0)
				step += step_size;
			x++;
		}
		jump += jump_size;
		y++;
	}
}

void	draw_line(t_mlx *mlx, float begin_x, float begin_y, float end_x, float end_y, int color)
{
	float delta_x;
	float delta_y;
	int pixel_count;
	float pixel_x;
	float pixel_y;
	
	delta_x = end_x - begin_x;
	delta_y = end_y - begin_y;
	pixel_count = sqrt((delta_x * delta_x) + (delta_y * delta_y));
	delta_x /= pixel_count;
	delta_y /= pixel_count;
	pixel_x = begin_x;
	pixel_y = begin_y;
	while (pixel_count)
	{
		my_mlx_pixel_put(mlx, pixel_x, pixel_y, color);
		pixel_x += delta_x;
		pixel_y += delta_y;
		--pixel_count;
	}
}