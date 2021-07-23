/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_screenres.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <lwiedijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/07 12:18:12 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/07/23 13:41:42 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../mlx/mlx.h"
#include <stdio.h>

void	check_screenres(t_maze *blueprint)
{
	if (blueprint->screenres_x == -1)
		blueprint->screenres_x = 800;
	if (blueprint->screenres_y == -1)
	{
		blueprint->screenres_y = 500;
		printf("No Screen-resolution is entered, size is set to default\n");
	}
	check_min_screensize(blueprint);
}

void	check_min_screensize(t_maze *blueprint)
{
	if (blueprint->screenres_x < TILE_SIZE)
	{
		printf("That is an unreasonably small resolution!\n");
		printf("screenwidth-resolution is resized\n");
		blueprint->screenres_x = TILE_SIZE;
	}
	if (blueprint->screenres_y < TILE_SIZE)
	{
		printf("That is an unreasonably small resolution!\n");
		printf("screenhight-resolution is resized\n");
		blueprint->screenres_y = TILE_SIZE;
	}
}

void	check_max_screensize(t_maze *blueprint, t_mlx mlx)
{
	int	max_x_res;
	int	max_y_res;

	mlx_get_screen_size(mlx.mlx, &max_x_res, &max_y_res);
	if (blueprint->screenres_x > max_x_res)
	{
		printf("your screenwidth-resolution is resized to MAX\n");
		blueprint->screenres_x = max_x_res;
	}
	if (blueprint->screenres_y > max_y_res)
	{
		printf("your screenhight-resolution is resized to MAX\n");
		blueprint->screenres_y = max_y_res;
	}
}
