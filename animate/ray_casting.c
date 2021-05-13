/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray_casting.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/12 10:14:49 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/05/13 14:44:37 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../mlx/mlx.h"
#include <math.h>
#include <stdio.h>
#include <limits.h>

double	distance_between_points(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	new_ray(t_port *port, t_rays *rays, double ray_angle, int playerx, int playery)
{
	int new_ray;
	double end_rayy;
	double end_rayx;
	double next_touchx;
	double next_touchy;
	double next_vert_touchy;
	double next_vert_touchx;
	double hit_x;
	double hit_y;
	double vert_hit_x;
	double vert_hit_y;
	double horz_distance;
	double vert_distance;

	hit_x = 0;
	hit_y = 0;
	vert_hit_x = 0;
	vert_hit_y = 0;

	end_rayy = port->player->pos_y + sin(ray_angle) * 30;
	end_rayx = port->player->pos_x + cos(ray_angle) * 30;
	//draw_line(port->mlx, playerx, playery, end_rayx, end_rayy, 0x805080);

	/* HORIZONTAL INTERCEPT */
	rays->hy_intercept = (playery / port->blueprint->tile_size) * port->blueprint->tile_size;
	rays->hx_intercept = playerx + (rays->hy_intercept - playery) / tan(ray_angle);
	/*if rays are pointing down*/
	if (ray_angle > 0 && ray_angle < M_PI)
		rays->hy_intercept += port->blueprint->tile_size;
	/*if rays are pointing up*/
	else
		rays->horz_ystep *= -1;
	rays->horz_xstep = port->blueprint->tile_size / tan(ray_angle);
	/*if rays are pointing right*/
	if (ray_angle < (0.5 * M_PI) || ray_angle > (1.5 * M_PI))
	{
		if (rays->horz_xstep < 0)
			rays->horz_xstep *= -1;

	}
	/*if rays are pointing left*/
	else
	{
		if (rays->horz_xstep > 0)
			rays->horz_xstep *= -1;
	}
	next_touchx = rays->hx_intercept;
	next_touchy = rays->hy_intercept;
	/*if ray is facing up*/
	if (ray_angle < 0 && ray_angle > M_PI)
		next_touchy--;
	while (1)
	{
		if (wall_hit(next_touchx, next_touchy, port))
		{
			hit_x = next_touchx;
			hit_y = next_touchy;
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
	rays->vx_intercept = (playerx / port->blueprint->tile_size) * port->blueprint->tile_size;
	rays->vy_intercept = playery + (rays->vx_intercept - playerx) * tan(ray_angle);
	/*if rays are pointing right*/
	if (ray_angle < (0.5 * M_PI) || ray_angle > (1.5 * M_PI))
		rays->vx_intercept += port->blueprint->tile_size;
	/*if rays are pointing left*/
	else
		rays->vert_xstep *= -1;
	rays->vert_ystep = port->blueprint->tile_size * tan(ray_angle);
	/*if ray is facing up*/
	if (ray_angle < 0 && ray_angle > M_PI)
	{
		if (rays->vert_ystep > 0)
			rays->vert_ystep *= -1;

	}
	/*if rays are pointing down*/
	if (ray_angle > 0 && ray_angle < M_PI)
	{
		if (rays->vert_ystep < 0)
			rays->vert_ystep *= -1;
	}
	next_vert_touchx = rays->vx_intercept;
	next_vert_touchy = rays->vy_intercept;
	/*if rays are pointing left*/
	if (ray_angle > (0.5 * M_PI) || ray_angle < (1.5 * M_PI))
		next_vert_touchx--;
	while (1)
	{
		if (wall_hit(next_vert_touchx, next_vert_touchy, port))
		{
			vert_hit_x = next_vert_touchx;
			vert_hit_y = next_vert_touchy;
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
	if (hit_x && hit_y)
		horz_distance = distance_between_points(playerx, playery, hit_x, hit_y);
	else
	{
		horz_distance = INT_MAX;
		hit_x = 1700;
		hit_y = 700;
	}
	if (vert_hit_x && vert_hit_y)
		vert_distance = distance_between_points(playerx, playery, vert_hit_x, vert_hit_y);
	else
	{
		vert_distance = INT_MAX;
		vert_hit_x = 1700;
		vert_hit_y = 700;
	}
	if (horz_distance < vert_distance)
		draw_line(port->mlx, playerx, playery, hit_x, hit_y, 0x805080);
	else
		draw_line(port->mlx, playerx, playery, vert_hit_x, vert_hit_y, 0x805080);



}

void	normalize_ray_angle(double *ray_angle)
{
	if (*ray_angle > (2 * M_PI))
		*ray_angle = fmod(*ray_angle, (2 * M_PI));
	if (*ray_angle < 0)
		*ray_angle = (2 * M_PI) + *ray_angle;
}

void	cast_all_rays(t_port *port, int playerx, int playery)
{
	int rays[port->rays->ray_num];
	double ray_angle;
	int colum_id;
	int i;

	i = 0;
	colum_id = 0;
	ray_angle = port->player->rotation - (port->rays->fov_angle / 2);
	//while (i < port->rays->ray_num)
	while (i < 1)
	{
		normalize_ray_angle(&ray_angle);
		new_ray(port, port->rays, ray_angle, playerx, playery);
		ray_angle += port->rays->fov_angle / port->rays->ray_num;
		i++;
	}
}
