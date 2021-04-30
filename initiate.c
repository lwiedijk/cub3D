/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initiate.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <lwiedijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/05 13:27:38 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/04/30 20:07:29 by lwiedijk      ########   odam.nl         */
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
	player->rotation = M_PI / 2;
	player->move_speed = 2.0;
	player->rotation_speed = 3 * (M_PI / 180);
}
