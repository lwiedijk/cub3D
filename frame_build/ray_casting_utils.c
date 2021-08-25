/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray_casting_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/19 16:27:27 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/08/25 11:49:54 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <math.h>

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

int	wall_hit(float x, float y, t_port *port)
{
	int	wall_pos_x;
	int	wall_pos_y;

	if (x <= 0 || x / TILE_SIZE >= port->blueprint->screenres_x)
		return (1);
	if (y <= 0 || y / TILE_SIZE >= port->blueprint->screenres_y)
		return (1);
	wall_pos_x = floor(x / TILE_SIZE);
	wall_pos_y = floor(y / TILE_SIZE);
	if (wall_pos_y >= (port->blueprint->map_y - 1))
		return (1);
	if (wall_pos_x >= (port->blueprint->map_x[wall_pos_y]))
		return (1);
	if (port->blueprint->map[wall_pos_y][wall_pos_x] > 0)
		return (1);
	return (0);
}
