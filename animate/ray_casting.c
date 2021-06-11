/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray_casting.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/12 10:14:49 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/06/11 12:25:01 by lwiedijk      ########   odam.nl         */
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

/*
**		Returns a color value from a coordinate of the texture image.
*/

int		put_north_texture(t_tex *tex, int x, int y)
{
	int	color;

	color = *(int*)(tex->addr_n + (y * tex->ls_n) + (x * (tex->bpp_n / 8)));
	return (color);
}

int		put_east_texture(t_tex *tex, int x, int y)
{
	int	color;

	color = *(int*)(tex->addr_e + (y * tex->ls_e) + (x * (tex->bpp_e / 8)));
	return (color);
}

int		put_south_texture(t_tex *tex, int x, int y)
{
	int	color;

	color = *(int*)(tex->addr_s + (y * tex->ls_s) + (x * (tex->bpp_s / 8)));
	return (color);
}

int		put_west_texture(t_tex *tex, int x, int y)
{
	int	color;

	color = *(int*)(tex->addr_w + (y * tex->ls_w) + (x * (tex->bpp_w / 8)));
	return (color);
}

void	render_walls(t_port *port, t_rays *rays, t_wall *wall_array, int colum_id)
{
	float	distance_to_plane;
	float	wall_striphight;
	int		x;
	int		tex_color;
	float	draw_start;
	float	draw_end;
	int		tex_x;
	int		tex_y;

	if (colum_id > rays->ray_num)
		return ;
	distance_to_plane = (port->blueprint->screenres_x / 2) / tan(rays->fov_angle / 2);
	wall_striphight = (port->blueprint->tile_size / wall_array[colum_id].raydistance) * distance_to_plane;
	rays->wall_striphight = wall_striphight;
	x = colum_id * rays->strip_width;
	draw_start = (port->blueprint->screenres_y / 2) - (wall_striphight / 2); 
	draw_end = draw_start + wall_striphight;
	if (wall_array[colum_id].vertical_hit)
		tex_x = (int)wall_array[colum_id].wall_hit_y % port->tex->x_n;
	else
		tex_x = (int)wall_array[colum_id].wall_hit_x % port->tex->x_n;
	if (wall_striphight > port->blueprint->screenres_y)
	{
		draw_end = port->blueprint->screenres_y;
		draw_start = 0;
	}
	rays->draw_start = draw_start;
	rays->draw_end = draw_end;
	if (wall_array[colum_id].wall_or == 'N')
	{
		calculate_textures(port, port->tex, wall_array[colum_id].wall_or);
		while (draw_start < draw_end)
		{
			tex_y = (int)port->tex->position & (port->tex->y_n - 1);
			port->tex->position += port->tex->step;
			tex_color = put_north_texture(port->tex, tex_x, tex_y);
			my_mlx_pixel_put(port->mlx, x, draw_start, tex_color);
			draw_start++;
		}
	}
	if (wall_array[colum_id].wall_or == 'E')
	{
		calculate_textures(port, port->tex, wall_array[colum_id].wall_or);
		while (draw_start < draw_end)
		{
			tex_y = (int)port->tex->position & (port->tex->y_e - 1);
			port->tex->position += port->tex->step;
			tex_color = put_east_texture(port->tex, tex_x, tex_y);
			my_mlx_pixel_put(port->mlx, x, draw_start, tex_color);
			draw_start++;
		}
	}
	if (wall_array[colum_id].wall_or == 'S')
	{
		calculate_textures(port, port->tex, wall_array[colum_id].wall_or);
		while (draw_start < draw_end)
		{
			tex_y = (int)port->tex->position & (port->tex->y_s - 1);
			port->tex->position += port->tex->step;
			tex_color = put_south_texture(port->tex, tex_x, tex_y);
			my_mlx_pixel_put(port->mlx, x, draw_start, tex_color);
			draw_start++;
		}
	}
	if (wall_array[colum_id].wall_or == 'W')
	{
		calculate_textures(port, port->tex, wall_array[colum_id].wall_or);
		while (draw_start < draw_end)
		{
			tex_y = (int)port->tex->position & (port->tex->y_w - 1);
			port->tex->position += port->tex->step;
			tex_color = put_west_texture(port->tex, tex_x, tex_y);
			my_mlx_pixel_put(port->mlx, x, draw_start, tex_color);
			draw_start++;
		}
	}
}

void	new_ray(t_port *port, t_rays *rays, double ray_angle, float playerx, float playery)
{
	float next_touchx;
	float next_touchy;
	float next_vert_touchy;
	float next_vert_touchx;
	float hor_hit_x;
	float hor_hit_y;
	float vert_hit_x;
	float vert_hit_y;
	float horz_distance;
	float vert_distance;
	int	found_hor_wallhit;
	int fount_vert_wallhit;
	int	hor_wall_content;
	int vert_wall_content;
	int	var;

	hor_hit_x = 0;
	hor_hit_y = 0;
	vert_hit_x = 0;
	vert_hit_y = 0;
	found_hor_wallhit = 0;
	fount_vert_wallhit = 0;
	hor_wall_content = 0;
	vert_wall_content = 0;
	var = 0;
	rays->ray_angle = ray_angle; //use normalized ray_angle
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
	if (rays->ray_left && rays->horz_xstep > 0)
			rays->horz_xstep *= -1;
	if (rays->ray_right && rays->horz_xstep < 0)
			rays->horz_xstep *= -1; 	
	next_touchx = rays->hx_intercept;
	next_touchy = rays->hy_intercept;
	if (rays->ray_up)
		var = 1;
	//while (next_touchx >= 0 && next_touchx / port->blueprint->tile_size <= port->blueprint->screenres_x
	//	&& next_touchy >= 0 && next_touchy / port->blueprint->tile_size <= port->blueprint->screenres_y)
	while (1)
	{
		if (wall_hit((next_touchx), (next_touchy - var), port, &hor_wall_content))
		{
			hor_hit_x = next_touchx;
			hor_hit_y = next_touchy;
			found_hor_wallhit = 1;
			break;
		}
		else
		{
			next_touchx += rays->horz_xstep;
			next_touchy += rays->horz_ystep;
		}
	}

	/* VERTICAL INTERCEPT */
	rays->vx_intercept = floor(playerx / port->blueprint->tile_size) * port->blueprint->tile_size;
	if (rays->ray_right)
		rays->vx_intercept += port->blueprint->tile_size;
	rays->vy_intercept = playery + (rays->vx_intercept - playerx) * tan(ray_angle);
	rays->vert_xstep = port->blueprint->tile_size;
	if (rays->ray_left)
		rays->vert_xstep *= -1;
	rays->vert_ystep = port->blueprint->tile_size * tan(ray_angle);
	if (rays->ray_up && rays->vert_ystep > 0)
		rays->vert_ystep *= -1;
	if (rays->ray_down && rays->vert_ystep < 0)
		rays->vert_ystep *= -1;
	next_vert_touchx = rays->vx_intercept;
	next_vert_touchy = rays->vy_intercept;
	var = 0;
	if (rays->ray_left)
		var = 1;
	//while (next_vert_touchx >= 0 && next_vert_touchx / port->blueprint->tile_size <= port->blueprint->screenres_x
	//	&& next_vert_touchy >= 0 && next_vert_touchy / port->blueprint->tile_size <= port->blueprint->screenres_y)
while (1)
	{
		if (wall_hit((next_vert_touchx - var), (next_vert_touchy - 0.0001), port, &vert_wall_content))
		{
			vert_hit_x = next_vert_touchx;
			vert_hit_y = next_vert_touchy;
			fount_vert_wallhit = 1;
			break;
		}
		else
		{
			next_vert_touchx += rays->vert_xstep;
			next_vert_touchy += rays->vert_ystep;
		}
	}

	/* WALL DISTANCE */
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
		rays->distance = horz_distance * cos(ray_angle - port->player->rotation);
		rays->wall_hit_x = hor_hit_x;
		rays->wall_hit_y = hor_hit_y;
		rays->vertical_hit = 0;
		if (rays->ray_up)
			rays->wall_or = 'N';
		else
			rays->wall_or = 'S';
		//draw_line(port->mlx, playerx, playery, hor_hit_x, hor_hit_y, 0x1605080);
	}
	else
	{
		rays->distance = vert_distance * cos(ray_angle - port->player->rotation);
		rays->wall_hit_x = vert_hit_x;
		rays->wall_hit_y = vert_hit_y;
		rays->vertical_hit = 1;
		if (rays->ray_right)
			rays->wall_or = 'E';
		else
			rays->wall_or = 'W';
		//draw_line(port->mlx, playerx, playery, vert_hit_x, vert_hit_y, 0x8020080);
	}
}

void	cast_all_rays(t_port *port, float playerx, float playery)
{
	t_wall wall_array[port->rays->ray_num];
	double ray_angle;
	int colum_id;
	int i;
	int dept;

	i = 0;
	colum_id = 0;
	ray_angle = port->player->rotation - (port->rays->fov_angle / 2);
	while (i < port->rays->ray_num)
	{
		normalize_ray_angle(&ray_angle);
		new_ray(port, port->rays, ray_angle, playerx, playery);
		wall_array[colum_id].raydistance = port->rays->distance;
		wall_array[colum_id].wall_or = port->rays->wall_or;
		wall_array[colum_id].wall_hit_x = port->rays->wall_hit_x;
		wall_array[colum_id].wall_hit_y = port->rays->wall_hit_y;
		wall_array[colum_id].vertical_hit = port->rays->vertical_hit;
		ray_angle += port->rays->fov_angle / port->rays->ray_num;
		colum_id++;
		i++;
	}
	colum_id = 0;
	while (colum_id < i)
	{
		//dept = 10000 / raydistance_array[colum_id];
		render_walls(port, port->rays, wall_array, colum_id);
		colum_id++;
	}
}


