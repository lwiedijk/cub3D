/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray_casting.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/12 10:14:49 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/05/20 18:13:23 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../mlx/mlx.h"
#include <math.h>
#include <stdio.h>
#include <limits.h>

float	distance_between_points(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	normalize_ray_angle(double *ray_angle)
{
	if (*ray_angle > (2 * M_PI))
		*ray_angle = fmod(*ray_angle, (2 * M_PI));
	if (*ray_angle < 0)
		*ray_angle = (2 * M_PI) + *ray_angle;
}

void	put_column(t_port *port, int x, float y, float wall_striphight, int color)
{
	int yi;
	float pos_y;
	float pos_x;

	if (wall_striphight > port->blueprint->screenres_y)
	{
		wall_striphight = port->blueprint->screenres_y;
		y = 0;
	}
	pos_y = y + wall_striphight;
	pos_x = x + port->rays->strip_width; 
	while (x < pos_x)
	{
		yi = y;
		while (yi < pos_y) 
		{
			my_mlx_pixel_put(port->mlx, x, yi, color);
			yi++;
		}
		x++;
	}
}

void	render_walls(t_port *port, t_rays *rays, double ray_distance, int colum_id)
{
	float	distance_to_plane;
	float	wall_striphight;
	int		x;
	float	y;

	//put_column(port, 0, 137.366455, 525.26709, 0x1605080);
	//put_square(port, 50, 300, 0x00FF00);
	if (colum_id > rays->ray_num)
		return ;
	distance_to_plane = (port->blueprint->screenres_x / 2) / tan(rays->fov_angle / 2);
	wall_striphight = (port->blueprint->tile_size / ray_distance) * distance_to_plane;
	x = colum_id * rays->strip_width;
	y = (port->blueprint->screenres_y / 2) - (wall_striphight / 2);
	//if (rays->columnid < rays->ray_num)
	put_column(port, x, y, wall_striphight, 0x16025080);
	//put_square(port, 50, 300, 0x00FF00);

}

void	new_ray(t_port *port, t_rays *rays, double ray_angle, int playerx, int playery)
{
	int new_ray;
	double end_rayy;
	double end_rayx;
	float next_touchx;
	float next_touchy;
	float next_vert_touchy;
	float next_vert_touchx;
	//double hit_x;
	//double hit_y;
	float hor_hit_x;
	float hor_hit_y;
	float vert_hit_x;
	float vert_hit_y;
	float horz_distance;
	float vert_distance;
	float	var;

	//put_square(port, 50, 300, 0x00FF00);
	hor_hit_x = 0;
	hor_hit_y = 0;
	vert_hit_x = 0;
	vert_hit_y = 0;
	var = 0;
	rays->ray_angle = ray_angle;

	//end_rayy = port->player->pos_y + sin(ray_angle) * 30;
	//end_rayx = port->player->pos_x + cos(ray_angle) * 30;
	//draw_line(port->mlx, playerx, playery, end_rayx, end_rayy, 0x805080);

	int	found_hor_wallhit = 0;
	int fount_vert_wallhit = 0;
	int	hor_wall_content = 0;
	int vert_wall_content = 0;

	//normalize_ray_angle(&ray_angle);
	rays->ray_down = ray_angle > 0 && ray_angle < M_PI;
	rays->ray_up = !rays->ray_down;
	rays->ray_right = ray_angle < (0.5 * M_PI) || ray_angle > (1.5 * M_PI);
	rays->ray_left = !rays->ray_right;

	/* HORIZONTAL INTERCEPT */
	rays->hy_intercept = floor(playery / port->blueprint->tile_size) * port->blueprint->tile_size;
	if (rays->ray_down)
		rays->hy_intercept += port->blueprint->tile_size;
	rays->hx_intercept = playerx + (rays->hy_intercept - playery) / tan(ray_angle);
	rays->horz_ystep = port->blueprint->tile_size;
	if (rays->ray_up)
		rays->horz_ystep *= -1;
	rays->horz_xstep = port->blueprint->tile_size / tan(ray_angle);
	/*if rays are pointing left*/
	if (rays->ray_left && rays->horz_xstep > 0)
			rays->horz_xstep *= -1;
	/*if rays are pointing right*/
	if (rays->ray_right && rays->horz_xstep < 0)
			rays->horz_xstep *= -1; 
			
	next_touchx = rays->hx_intercept;
	next_touchy = rays->hy_intercept;
	/*if ray is facing up*/
	if (rays->ray_up)
		//next_touchy--;
		var = 1;
	while (1)
	{
		//if (rays->hx_intercept == playerx && rays->hy_intercept == playery)
		//{
		//	hor_hit_x = playerx;
		//	hor_hit_y = playery;
		//	found_hor_wallhit = 1;
		//	break;
		//}
		if (wall_hit((next_touchx), (next_touchy - var), port, &hor_wall_content))
		{
			hor_hit_x = next_touchx;
			hor_hit_y = next_touchy;
			found_hor_wallhit = 1;
			//draw_line(port->mlx, playerx, playery, hit_x, hit_y, 0x805080);
			break;
		}
		else
		{
			next_touchx += rays->horz_xstep;
			next_touchy += rays->horz_ystep;
		}
	}
	//draw_line(port->mlx, playerx, playery, hit_x, hit_y, 0x805080);

	/*VERTICAL INTERCEPT*/
	rays->vx_intercept = floor(playerx / port->blueprint->tile_size) * port->blueprint->tile_size;
	/*if rays are pointing right*/
	if (rays->ray_right)
		rays->vx_intercept += port->blueprint->tile_size;
	rays->vy_intercept = playery + (rays->vx_intercept - playerx) * tan(ray_angle);
	rays->vert_xstep = port->blueprint->tile_size;
	/*if rays are pointing left*/
	if (rays->ray_left)
	{
		rays->vert_xstep *= -1;
	}
	rays->vert_ystep = port->blueprint->tile_size * tan(ray_angle);
	/*if ray is facing up*/
	if (rays->ray_up && rays->vert_ystep > 0)
		rays->vert_ystep *= -1;
	/*if rays are pointing down*/
	if (rays->ray_down && rays->vert_ystep < 0)
		rays->vert_ystep *= -1;
	next_vert_touchx = rays->vx_intercept;
	next_vert_touchy = rays->vy_intercept;
	/*if rays are pointing left*/
	var = 0;
	if (rays->ray_left)
		//next_vert_touchx--;
		var = 1;
	while (1)
	{
		//if (rays->vx_intercept == playerx && rays->vy_intercept == playery)
		//{
		//	vert_hit_x = playerx;
		//	vert_hit_y = playery;
		//	fount_vert_wallhit = 1;
		//	break;
		//}
		if (wall_hit((next_vert_touchx - var), (next_vert_touchy - 0.0001), port, &vert_wall_content))
		{
			vert_hit_x = next_vert_touchx;
			vert_hit_y = next_vert_touchy;
			fount_vert_wallhit = 1;
			//draw_line(port->mlx, playerx, playery, vert_hit_x, vert_hit_y, 0x805080);
			break;
		}
		else
		{
			next_vert_touchx += rays->vert_xstep;
			next_vert_touchy += rays->vert_ystep;
		}
	}
	//draw_line(port->mlx, playerx, playery, hit_x, hit_y, 0x805080);
	if (found_hor_wallhit)
		horz_distance = distance_between_points(playerx, playery, hor_hit_x, hor_hit_y);
	else
		horz_distance = INT_MAX;
	if (fount_vert_wallhit)
		vert_distance = distance_between_points(playerx, playery, vert_hit_x, vert_hit_y);
	else
		vert_distance = INT_MAX;
	if (horz_distance <= vert_distance)
	{
		//render_walls(port, port->rays, horz_distance);
		rays->distance = horz_distance * cos(ray_angle - port->player->rotation);
//		draw_line(port->mlx, playerx, playery, hor_hit_x, hor_hit_y, 0x1605080);
		//put_square(port, 50, 300, 0x00FF00);
	}
	else
	{
		//render_walls(port, port->rays, vert_distance);
		rays->distance = vert_distance * cos(ray_angle - port->player->rotation);
//		draw_line(port->mlx, playerx, playery, vert_hit_x, vert_hit_y, 0x8020080);
		//put_square(port, 150, 300, 0x00FF00);
	}
}

void	cast_all_rays(t_port *port, int playerx, int playery)
{
	double raydistance_array[port->rays->ray_num];
	double ray_angle;
	int colum_id;
	int i;

	i = 0;
	colum_id = 0;
	ray_angle = port->player->rotation - (port->rays->fov_angle / 2);
	while (i < port->rays->ray_num)
	{
		normalize_ray_angle(&ray_angle);
		new_ray(port, port->rays, ray_angle, playerx, playery);
		raydistance_array[colum_id] = port->rays->distance;
		ray_angle += port->rays->fov_angle / port->rays->ray_num;
		colum_id++;
		i++;
	}
	colum_id = 0;
	while (colum_id < i)
	{
		render_walls(port, port->rays, raydistance_array[colum_id], colum_id);
		colum_id++;
	}
}
