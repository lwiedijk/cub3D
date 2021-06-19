/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray_casting_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/19 16:27:27 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/06/19 16:28:19 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"
#include "../mlx/mlx.h"
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
