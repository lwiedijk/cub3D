/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray_casting.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/12 10:14:49 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/06/12 14:38:45 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../mlx/mlx.h"
#include <math.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

float	distance_between_points(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	normalize_ray_angle(float *ray_angle)
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
	wall_striphight = (TILE_SIZE / wall_array[colum_id].raydistance) * distance_to_plane;
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

void	horizontal_intercept(t_rays *rays, t_player *player)
{
	rays->hy_intercept = floor(player->pos_y / TILE_SIZE) * TILE_SIZE;
	if (rays->ray_down)
		rays->hy_intercept += TILE_SIZE;
	rays->hx_intercept = player->pos_x
		+ (rays->hy_intercept - player->pos_y) / tan(rays->ray_angle);
	rays->horz_ystep = TILE_SIZE;
	if (rays->ray_up)
		rays->horz_ystep *= -1;
	rays->horz_xstep = TILE_SIZE / tan(rays->ray_angle);
	if (rays->ray_left && rays->horz_xstep > 0)
		rays->horz_xstep *= -1;
	if (rays->ray_right && rays->horz_xstep < 0)
		rays->horz_xstep *= -1;
}

void	check_horizontal_wallhit(t_port *port, t_rays *rays, t_maze *maze)
{
	float	next_touchx;
	float	next_touchy;
	int		var;

	next_touchx = rays->hx_intercept;
	next_touchy = rays->hy_intercept;
	var = 0;
	if (rays->ray_up)
		var = 1;
	while (next_touchx >= 0 && next_touchx / TILE_SIZE <= maze->screenres_x
		&& next_touchy >= 0 && next_touchy / TILE_SIZE <= maze->screenres_y)
	{
		if (wall_hit((next_touchx), (next_touchy - var), port))
		{
			rays->hor_hit_x = next_touchx;
			rays->hor_hit_y = next_touchy;
			rays->found_hor_wallhit = 1;
			break ;
		}
		else
		{
			next_touchx += rays->horz_xstep;
			next_touchy += rays->horz_ystep;
		}
	}
}

void	vertical_intercept(t_rays *rays, t_player *player)
{
	rays->vx_intercept = floor(player->pos_x / TILE_SIZE) * TILE_SIZE;
	if (rays->ray_right)
		rays->vx_intercept += TILE_SIZE;
	rays->vy_intercept = player->pos_y
		+ (rays->vx_intercept - player->pos_x) * tan(rays->ray_angle);
	rays->vert_xstep = TILE_SIZE;
	if (rays->ray_left)
		rays->vert_xstep *= -1;
	rays->vert_ystep = TILE_SIZE * tan(rays->ray_angle);
	if (rays->ray_up && rays->vert_ystep > 0)
		rays->vert_ystep *= -1;
	if (rays->ray_down && rays->vert_ystep < 0)
		rays->vert_ystep *= -1;
}

void	check_vertical_wallhit(t_port *port, t_rays *rays, t_maze *maze)
{
	float	next_touchy;
	float	next_touchx;
	int		var;

	next_touchx = rays->vx_intercept;
	next_touchy = rays->vy_intercept;
	var = 0;
	if (rays->ray_left)
		var = 1;
	while (next_touchx >= 0 && next_touchx / TILE_SIZE <= maze->screenres_x
		&& next_touchy >= 0 && next_touchy / TILE_SIZE <= maze->screenres_y)
	{
		if (wall_hit((next_touchx - var), (next_touchy - 0.0001), port))
		{
			rays->vert_hit_x = next_touchx;
			rays->vert_hit_y = next_touchy;
			rays->fount_vert_wallhit = 1;
			break ;
		}
		else
		{
			next_touchx += rays->vert_xstep;
			next_touchy += rays->vert_ystep;
		}
	}
}

void	new_ray(t_port *port, t_rays *rays, t_player *player, int colum_id)
{
	float	horz_distance;
	float	vert_distance;

	rays->ray_down = rays->ray_angle > 0 && rays->ray_angle < M_PI;
	rays->ray_up = !rays->ray_down;
	rays->ray_right = rays->ray_angle < (0.5 * M_PI) || rays->ray_angle > (1.5 * M_PI);
	rays->ray_left = !rays->ray_right;
	horizontal_intercept(rays, player);
	check_horizontal_wallhit(port, rays, port->blueprint);
	vertical_intercept(rays, player);
	check_vertical_wallhit(port, rays, port->blueprint);
	
	/* WALL DISTANCE */
	if (rays->found_hor_wallhit)
		horz_distance = distance_between_points(player->pos_x, player->pos_y, rays->hor_hit_x, rays->hor_hit_y);		
	else
		horz_distance = INT_MAX;
	if (rays->fount_vert_wallhit)
		vert_distance = distance_between_points(player->pos_x, player->pos_y, rays->vert_hit_x, rays->vert_hit_y);
	else
		vert_distance = INT_MAX;
	if (horz_distance <= vert_distance)
	{
		//rays->distance = horz_distance * cos(rays->ray_angle - port->player->rotation);
		port->wall_array[colum_id].raydistance = horz_distance * cos(rays->ray_angle - port->player->rotation);
		rays->wall_hit_x = rays->hor_hit_x;
		rays->wall_hit_y = rays->hor_hit_y;
		rays->vertical_hit = 0;
		if (rays->ray_up)
			rays->wall_or = 'N';
		else
			rays->wall_or = 'S';
		//draw_line(port->mlx, playerx, playery, hor_hit_x, hor_hit_y, 0x1605080);
	}
	else
	{
		//rays->distance = vert_distance * cos(rays->ray_angle - port->player->rotation);
		port->wall_array[colum_id].raydistance = vert_distance * cos(rays->ray_angle - port->player->rotation);
		rays->wall_hit_x = rays->vert_hit_x;
		rays->wall_hit_y = rays->vert_hit_y;
		rays->vertical_hit = 1;
		if (rays->ray_right)
			rays->wall_or = 'E';
		else
			rays->wall_or = 'W';
		//draw_line(port->mlx, playerx, playery, vert_hit_x, vert_hit_y, 0x8020080);
	}
}

void	cast_all_rays(t_port *port)
{
	//float	ray_angle;
	int		colum_id;
	int		i;
	int		dept;
	t_wall	*wall_array;

	wall_array = (t_wall *)malloc(sizeof(t_wall) * port->rays->ray_num);
	i = 0;
	colum_id = 0;
	port->rays->ray_angle = port->player->rotation - (port->rays->fov_angle / 2);
	while (i < port->rays->ray_num)
	{
		normalize_ray_angle(&port->rays->ray_angle);
		port->wall_array = wall_array; //hoger?
		init_rays(port->rays, port->blueprint);
		new_ray(port, port->rays, port->player, colum_id);
		//wall_array[colum_id].raydistance = port->rays->distance;
		wall_array[colum_id].wall_or = port->rays->wall_or;
		wall_array[colum_id].wall_hit_x = port->rays->wall_hit_x;
		wall_array[colum_id].wall_hit_y = port->rays->wall_hit_y;
		wall_array[colum_id].vertical_hit = port->rays->vertical_hit;
		port->rays->ray_angle += port->rays->fov_angle / port->rays->ray_num;
		colum_id++;
		i++;
	}
	colum_id = 0;
	while (colum_id < i)
	{
		render_walls(port, port->rays, wall_array, colum_id);
		colum_id++;
	}
	free(wall_array);
}
