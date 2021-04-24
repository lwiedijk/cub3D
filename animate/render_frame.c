/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_frame.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <lwiedijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/05 15:35:38 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/04/17 10:21:15 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../mlx/mlx.h"
#include <stdio.h>

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

void	put_square(t_port *port, int x, int y, int color)
{
	int xi;
	int pos_y;
	int pos_x;

	pos_y = y + 20;
	pos_x = x + 20;
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

void	put_player(t_port *port, int x, int y, int color)
{
	int xi;
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
	while (y < pos_y - 4)
	{
		xi = x;
		while (xi < pos_x + 5) 
		{
			my_mlx_pixel_put(port->mlx, xi, y, color);
			xi++;
		}
		y++;
	}
}

int	render_frame(t_port *port)
{
	int		x;
	int 	y;
	int		line_start;
	int 	line_end;
	int step;
	int jump;

	x = 0;
	y = 0;
	int jump_size = 20;
	int step_size = 20;
	jump = 0;
	step = 0;
	port->mlx->img_1 = mlx_new_image(port->mlx->mlx, 1900, 800);
	port->mlx->addr = mlx_get_data_addr(port->mlx->img_1, &port->mlx->bits_per_pixel,
	&port->mlx->line_length, &port->mlx->endian);
	//put_square(port, 0, 0, port->blueprint->ceiling_color);
	//put_square(port, 50, 70, 0xFF0000);
	//put_square(port, 390, 230, port->blueprint->floor_color);
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
	put_player(port, (port->player->pos_x * step_size), (port->player->pos_y * step_size), 0xFF0000);//player
	mlx_put_image_to_window(port->mlx->mlx, port->mlx->win, port->mlx->img_1, 0, 0);
	return (0);
}