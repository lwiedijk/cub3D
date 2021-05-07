/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_frame.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <lwiedijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/05 15:35:38 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/05/07 17:27:57 by lwiedijk      ########   odam.nl         */
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

void	animate(t_port *port)
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

void	new_ray(t_port *port, double ray_angle, int playerx, int playery)
{
	int new_ray;
	double end_rayy;
	double end_rayx;

	end_rayy = port->player->pos_y + sin(ray_angle) * 30;
	end_rayx = port->player->pos_x + cos(ray_angle) * 30;
	draw_line(port->mlx, playerx, playery, end_rayx, end_rayy, 0xFFFF00); 
}

void	cast_all_rays(t_port *port, int playerx, int playery)
{
	int rays[port->rays->ray_num];
	int ray;
	double ray_angle;
	int colum_id;
	int i;

	i = 0;
	colum_id = 0;
	ray_angle = port->player->rotation - (port->rays->fov_angle / 2);
	while (i < port->rays->ray_num)
	{
		new_ray(port, ray_angle, playerx, playery);
		ray_angle += port->rays->fov_angle / port->rays->ray_num;
		i++;
	}
}

void	next_frame(t_mlx *mlx)
{
	mlx->img_2 = mlx->img_1;
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img_2, 0, 0);
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
	animate(port);
	if (port->mlx->img_1)
		next_frame(port->mlx);
	port->mlx->img_1 = mlx_new_image(port->mlx->mlx, port->blueprint->screenres_x, port->blueprint->screenres_y);
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
	put_player(port, (port->player->pos_x), (port->player->pos_y), 0xFF0000);//player
	cast_all_rays(port, port->player->pos_x, port->player->pos_y);
	mlx_put_image_to_window(port->mlx->mlx, port->mlx->win, port->mlx->img_1, 0, 0);
	if (port->mlx->img_2)
		mlx_destroy_image(port->mlx->mlx, port->mlx->img_2);
	return (0);
}
