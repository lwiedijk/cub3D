/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray_casting.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/12 10:14:49 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/05/12 10:56:40 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../mlx/mlx.h"
#include <math.h>

void	new_ray(t_port *port, double ray_angle, int playerx, int playery)
{
	int new_ray;
	double end_rayy;
	double end_rayx;

	end_rayy = port->player->pos_y + sin(ray_angle) * 30;
	end_rayx = port->player->pos_x + cos(ray_angle) * 30;
	draw_line(port->mlx, playerx, playery, end_rayx, end_rayy, 0x805080); 
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
