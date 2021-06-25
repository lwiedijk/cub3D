/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initiate.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <lwiedijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/05 13:27:38 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/06/25 14:53:10 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stddef.h>
#include <math.h>

void	init_maze(t_maze *blueprint)
{
	blueprint->filepos = 0;
	blueprint->screenres_y = 0;
	blueprint->screenres_x = 0;
	blueprint->north_texture = 0;
	blueprint->east_texture = 0;
	blueprint->south_texture = 0;
	blueprint->west_texture = 0;
	blueprint->sprite = 0;
	blueprint->floor_color = 0;
	blueprint->ceiling_color = 0;
	blueprint->r = 0;
	blueprint->g = 0;
	blueprint->b = 0;
	blueprint->map_y = 0;
	blueprint->map_x = 0;
	blueprint->map = 0;
	//blueprint->tile_size = 64;
	blueprint->step_size = SCALE * TILE_SIZE;
	blueprint->player_or = 0;
}

void	init_mlx(t_mlx *mlx)
{
	mlx->mlx = 0;
	mlx->win = 0;
	mlx->img_1 = 0;
	mlx->img_2 = 0;
	mlx->addr = 0;
	mlx->bits_per_pixel = 0;
	mlx->line_length = 0;
	mlx->endian = 0;
	mlx->next_frame = 0;
}

void	init_player(t_player *player)
{
	player->pos_x = 0;
	player->pos_y = 0;
	player->walkdirection = 0;
	player->turndirection = 0;
	player->strafe = 0;
	player->rotation = 0;
	player->move_speed = 2.0;
	player->rotation_speed = 2 * (M_PI / 180);
}

void	init_rays(t_rays *rays, t_maze *blueprint)
{
	rays->fov_angle = 60 * (M_PI / 180);
	rays->strip_width = 1;
	rays->ray_num = blueprint->screenres_x / rays->strip_width;
	//rays->hx_intercept = 0;
	//rays->hy_intercept = 0;
	//rays->vx_intercept = 0;
	//rays->vy_intercept = 0;
	//rays->horz_xstep = 0;
	//rays->horz_ystep = 0;
	//rays->vert_xstep = 0;
	//rays->vert_ystep = 0;
	//rays->distance = 0;
	//rays->columnid = 0;
	//rays->hor_hit_x = 0;
	//rays->hor_hit_y = 0;
	//rays->vert_hit_x = 0;
	//rays->vert_hit_y = 0;
	rays->found_hor_wallhit = 0;
	rays->fount_vert_wallhit = 0;	
}
