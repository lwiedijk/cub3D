/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initiate.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <lwiedijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/05 13:27:38 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/08/25 13:10:22 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stddef.h>
#include <math.h>

void	init_maze(t_maze *blueprint)
{
	blueprint->mapfile = NULL;
	blueprint->filepos = 0;
	blueprint->screenres_y = -1;
	blueprint->screenres_x = -1;
	blueprint->north_texture = 0;
	blueprint->east_texture = 0;
	blueprint->south_texture = 0;
	blueprint->west_texture = 0;
	blueprint->floor_color = -1;
	blueprint->ceiling_color = -1;
	blueprint->sprite = 0;
	blueprint->r = 0;
	blueprint->g = 0;
	blueprint->b = 0;
	blueprint->map_y = 0;
	blueprint->map_x = 0;
	blueprint->map = 0;
	blueprint->jump = 0;
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
	player->forward = 0;
	player->backward = 0;
	player->turndirection_r = 0;
	player->turndirection_l = 0;
	player->strafe_r = 0;
	player->strafe_l = 0;
	player->rotation = 0;
	player->move_speed = 2.0;
	player->rotation_speed = 1 * (M_PI / 180);
}

void	init_rays(t_rays *rays, t_maze *blueprint)
{
	rays->fov_angle = 60 * (M_PI / 180);
	rays->strip_width = 1;
	rays->dist_to_plane = (blueprint->screenres_x / 2)
		/ tan(rays->fov_angle / 2);
	rays->ray_num = blueprint->screenres_x / rays->strip_width;
	rays->found_hor_wallhit = 0;
	rays->fount_vert_wallhit = 0;
}

void	init_tex(t_tex *tex)
{
	tex->tex_array = NULL;
}
