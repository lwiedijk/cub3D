/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray_casting.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/12 10:14:49 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/06/16 17:11:32 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"
#include "../mlx/mlx.h"
#include <math.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

//->raycasting utils 

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

void	ray_direction(t_rays *rays)
{
	rays->ray_down = rays->ray_angle > 0 && rays->ray_angle < M_PI;
	rays->ray_up = !rays->ray_down;
	rays->ray_right = rays->ray_angle < (0.5 * M_PI)
		|| rays->ray_angle > (1.5 * M_PI);
	rays->ray_left = !rays->ray_right;
}

/*
**		Returns a color value from a coordinate of the texture image.
*/

void	put_north_texture(t_port *port, t_tex *tex, t_rays *rays, int colum_id)
{
	int	tex_color;

	calculate_textures(port, port->tex, port->wall_array[colum_id].wall_or);
	while (rays->draw_start < rays->draw_end)
	{
		tex->tex_y = (int)port->tex->position & (port->tex->y_n - 1);
		port->tex->position += port->tex->step;
		tex_color = *(int *)(tex->addr_n + (tex->tex_y * tex->ls_n)
				+ (tex->tex_x * (tex->bpp_n / 8)));
		my_mlx_pixel_put(port->mlx, colum_id, rays->draw_start, tex_color);
		rays->draw_start++;
	}
}

void	put_east_texture(t_port *port, t_tex *tex, t_rays *rays, int colum_id)
{
	int	tex_color;

	calculate_textures(port, port->tex, port->wall_array[colum_id].wall_or);
	while (rays->draw_start < rays->draw_end)
	{
		tex->tex_y = (int)port->tex->position & (port->tex->y_e - 1);
		port->tex->position += port->tex->step;
		tex_color = *(int *)(tex->addr_e + (tex->tex_y * tex->ls_e)
				+ (tex->tex_x * (tex->bpp_e / 8)));
		my_mlx_pixel_put(port->mlx, colum_id, rays->draw_start, tex_color);
		rays->draw_start++;
	}
}

void	put_south_texture(t_port *port, t_tex *tex, t_rays *rays, int colum_id)
{
	int	tex_color;

	calculate_textures(port, port->tex, port->wall_array[colum_id].wall_or);
	while (rays->draw_start < rays->draw_end)
	{
		tex->tex_y = (int)port->tex->position & (port->tex->y_s - 1);
		port->tex->position += port->tex->step;
		tex_color = *(int *)(tex->addr_s + (tex->tex_y * tex->ls_s)
				+ (tex->tex_x * (tex->bpp_s / 8)));
		my_mlx_pixel_put(port->mlx, colum_id, rays->draw_start, tex_color);
		rays->draw_start++;
	}
}

void	put_west_texture(t_port *port, t_tex *tex, t_rays *rays, int colum_id)
{
	int	tex_color;

	calculate_textures(port, port->tex, port->wall_array[colum_id].wall_or);
	while (rays->draw_start < rays->draw_end)
	{
		tex->tex_y = (int)port->tex->position & (port->tex->y_w - 1);
		port->tex->position += port->tex->step;
		tex_color = *(int *)(tex->addr_w + (tex->tex_y * tex->ls_w)
				+ (tex->tex_x * (tex->bpp_w / 8)));
		my_mlx_pixel_put(port->mlx, colum_id, rays->draw_start, tex_color);
		rays->draw_start++;
	}
}

void	put_all_textures(t_port *port, t_wall *wall_array, int colum_id)
{
	if (wall_array[colum_id].vertical_hit)
		port->tex->tex_x = (int)wall_array[colum_id].wall_hit_y
			% port->tex->x_n;
	else
		port->tex->tex_x = (int)wall_array[colum_id].wall_hit_x
			% port->tex->x_n;
	if (wall_array[colum_id].wall_or == 'N')
		put_north_texture(port, port->tex, port->rays, colum_id);
	if (wall_array[colum_id].wall_or == 'E')
		put_east_texture(port, port->tex, port->rays, colum_id);
	if (wall_array[colum_id].wall_or == 'S')
		put_south_texture(port, port->tex, port->rays, colum_id);
	if (wall_array[colum_id].wall_or == 'W')
		put_west_texture(port, port->tex, port->rays, colum_id);
	draw_line(port->mlx, (SCALE * port->player->pos_x),
		(SCALE * port->player->pos_y),
		(SCALE * wall_array[colum_id].wall_hit_x),
		(SCALE * wall_array[colum_id].wall_hit_y), 0xFFFF00);
}

void	render_walls(t_port *port, t_rays *rays,
		t_wall *wall_array, int colum_id)
{
	float	distance_to_plane;

	if (colum_id > rays->ray_num)
		return ;
	distance_to_plane = (port->blueprint->screenres_x / 2)
		/ tan(rays->fov_angle / 2);
	rays->wall_striphight = (TILE_SIZE / wall_array[colum_id].raydistance)
		* distance_to_plane;
	rays->draw_start = (port->blueprint->screenres_y / 2)
		- (rays->wall_striphight / 2);
	rays->draw_end = rays->draw_start + rays->wall_striphight;
	if (rays->wall_striphight > port->blueprint->screenres_y)
	{
		rays->draw_end = port->blueprint->screenres_y;
		rays->draw_start = 0;
	}
	put_all_textures(port, wall_array, colum_id);
}

void	set_horizontal_ray(t_wall *wall_array, t_rays *rays,
		t_player *player, int colum_id)
{
	wall_array[colum_id].raydistance = rays->horz_distance
		* cos(rays->ray_angle - player->rotation);
	wall_array[colum_id].wall_hit_x = rays->hor_hit_x;
	wall_array[colum_id].wall_hit_y = rays->hor_hit_y;
	wall_array[colum_id].vertical_hit = 0;
	if (rays->ray_up)
		wall_array[colum_id].wall_or = 'N';
	else
		wall_array[colum_id].wall_or = 'S';
}

void	set_vertical_ray(t_wall *wall_array, t_rays *rays,
		t_player *player, int colum_id)
{
	wall_array[colum_id].raydistance = rays->vert_distance
		* cos(rays->ray_angle - player->rotation);
	wall_array[colum_id].wall_hit_x = rays->vert_hit_x;
	wall_array[colum_id].wall_hit_y = rays->vert_hit_y;
	wall_array[colum_id].vertical_hit = 1;
	if (rays->ray_right)
		wall_array[colum_id].wall_or = 'E';
	else
		wall_array[colum_id].wall_or = 'W';
}

void	check_distance_to_wall(t_rays *rays, t_player *player,
		t_wall *wall_array, int colum_id)
{
	if (rays->found_hor_wallhit)
		rays->horz_distance = distance_between_points(player->pos_x,
				player->pos_y, rays->hor_hit_x, rays->hor_hit_y);
	else
		rays->horz_distance = INT_MAX;
	if (rays->fount_vert_wallhit)
		rays->vert_distance = distance_between_points(player->pos_x,
				player->pos_y, rays->vert_hit_x, rays->vert_hit_y);
	else
		rays->vert_distance = INT_MAX;
	if (rays->horz_distance <= rays->vert_distance)
		set_horizontal_ray(wall_array, rays, player, colum_id);
	else
		set_vertical_ray(wall_array, rays, player, colum_id);
}

void	new_ray(t_port *port, t_rays *rays, t_player *player, int colum_id)
{
	normalize_ray_angle(&rays->ray_angle);
	init_rays(rays, port->blueprint);
	ray_direction(rays);
	horizontal_intercept(rays, player);
	check_horizontal_wallhit(port, rays, port->blueprint);
	vertical_intercept(rays, player);
	check_vertical_wallhit(port, rays, port->blueprint);
	check_distance_to_wall(rays, player, port->wall_array, colum_id);
}

void	cast_all_rays(t_port *port, t_rays *rays)
{
	int		colum_id;
	int		i;
	t_wall	*wall_array;

	wall_array = (t_wall *)malloc(sizeof(t_wall) * rays->ray_num);
	if (!wall_array)
		ft_error(2);
	port->wall_array = wall_array;
	i = 0;
	colum_id = 0;
	rays->ray_angle = port->player->rotation - (rays->fov_angle / 2);
	while (i < rays->ray_num)
	{
		new_ray(port, rays, port->player, colum_id);
		rays->ray_angle += rays->fov_angle / rays->ray_num;
		colum_id++;
		i++;
	}
	colum_id = 0;
	while (colum_id < i)
	{
		render_walls(port, rays, wall_array, colum_id);
		colum_id++;
	}
	free(wall_array);
}
