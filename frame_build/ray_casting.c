/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray_casting.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/12 10:14:49 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/06/30 15:55:36 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"
#include "../mlx/mlx.h"
#include <math.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

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
		ft_error(MALLOC_FAIL);
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
		draw_walls(port, rays, wall_array, colum_id);
		colum_id++;
	}
	free(wall_array);
}
