/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_frame.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <lwiedijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/05 15:35:38 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/06/16 11:39:12 by lwiedijk      ########   odam.nl         */
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
	*(unsigned int *)dst = color;
}

int	put_color(int t, int r, int g, int b) // put in libft!
{
	int	color;

	color = ((t & 0xff) << 24) + ((r & 0xff) << 16)
		+ ((g & 0xff) << 8) + (b & 0xff);
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
	port->mlx->img_1 = mlx_new_image(port->mlx->mlx,
			port->blueprint->screenres_x, port->blueprint->screenres_y);
	port->mlx->addr = mlx_get_data_addr(port->mlx->img_1,
			&port->mlx->bits_per_pixel, &port->mlx->line_length,
			&port->mlx->endian);
	put_wall_ceiling(port, port->blueprint);
	cast_all_rays(port, port->rays);
	draw_2d_map(port);
	draw_player(port, (SCALE * port->player->pos_x),
		(SCALE * port->player->pos_y), 0x0000FF);
	mlx_put_image_to_window(port->mlx->mlx, port->mlx->win,
		port->mlx->img_1, 0, 0);
	if (port->mlx->img_2)
		mlx_destroy_image(port->mlx->mlx, port->mlx->img_2);
	return (0);
}
