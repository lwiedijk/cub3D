/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_frame.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <lwiedijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/05 15:35:38 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/05/20 14:42:50 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../mlx/mlx.h"
#include <stdio.h>
#include <math.h>

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;
	
	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	put_color(int r, int g, int b)
{
	int color;

	color = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	return (color);
}

void	put_wall_ceiling(t_port *port, t_maze *blueprint)
{
	int	x;
	int	y;

	y = 0;
	while (y < (blueprint->screenres_y / 2))
	{
		x = 0;
		while (x < blueprint->screenres_x)
		{
			my_mlx_pixel_put(port->mlx, x, y, blueprint->ceiling_color);
			x++;
		}
		y++;
	}
	y = (blueprint->screenres_y / 2);
	while (y < blueprint->screenres_y)
	{
		x = 0;
		while (x < blueprint->screenres_x)
		{
			my_mlx_pixel_put(port->mlx, x, y, blueprint->floor_color);
			x++;
		}
		y++;
	}
}

void	put_square(t_port *port, int x, int y, int color)
{
	int xi;
	int pos_y;
	int pos_x;

	pos_y = y + port->blueprint->tile_size;
	pos_x = x + port->blueprint->tile_size;
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
	int		x;
	int 	y;
	int step;
	int jump;
	int jump_size;
	int step_size;

	y = 0;
	jump = 0;
	jump_size = port->blueprint->tile_size;
	step_size = port->blueprint->jump_size;

	while(y < port->blueprint->map_y)
	{
		x = 0;
		step = 0;
		while (x < port->blueprint->map_x[y])
		{
			if (port->blueprint->map[y][x] > 0 && port->blueprint->map[y][x] < 2) //walls
			{
				put_square(port, step, jump, 0x00FF00);
				step += step_size;
			}
			if (port->blueprint->map[y][x] == 2)//sprite
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

void	draw_line(t_mlx *mlx, double begin_x, double begin_y, double end_x, double end_y, int color)
{
	double delta_x;
	double delta_y;
	int pixel_count;
	double pixel_x;
	double pixel_y;
	
	delta_x = end_x - begin_x;
	delta_y = end_y - begin_y;
	pixel_count = sqrt((delta_x * delta_x) + (delta_y * delta_y)); // pytagoras
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

void	next_frame(t_mlx *mlx)
{
	mlx->img_2 = mlx->img_1;
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img_2, 0, 0);
}

int	render_frame(t_port *port)
{
	walk_player(port);
	if (port->mlx->img_1)
		next_frame(port->mlx);
	port->mlx->img_1 = mlx_new_image(port->mlx->mlx, port->blueprint->screenres_x, port->blueprint->screenres_y);
	port->mlx->addr = mlx_get_data_addr(port->mlx->img_1, &port->mlx->bits_per_pixel,
	&port->mlx->line_length, &port->mlx->endian);
	//draw_2d_map(port);
	put_wall_ceiling(port, port->blueprint);
	cast_all_rays(port, port->player->pos_x, port->player->pos_y);
	//draw_player(port, (port->player->pos_x), (port->player->pos_y), 0xFF0000);//player
	mlx_put_image_to_window(port->mlx->mlx, port->mlx->win, port->mlx->img_1, 0, 0);
	if (port->mlx->img_2)
		mlx_destroy_image(port->mlx->mlx, port->mlx->img_2);
	return (0);
}
