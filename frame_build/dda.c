/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dda.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/16 13:50:36 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/08/25 11:47:40 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <math.h>

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
