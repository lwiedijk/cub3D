/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_screenres.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <lwiedijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/07 12:18:12 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/07/07 12:24:55 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../mlx/mlx.h"

void	check_max_screensize(t_maze *blueprint, t_mlx mlx)
{
	int	max_x_res;
	int	max_y_res;

	mlx_get_screen_size(mlx.mlx, &max_x_res, &max_y_res);
	if (blueprint->screenres_x > max_x_res)
		blueprint->screenres_x = max_x_res;
	if (blueprint->screenres_y > max_y_res)
		blueprint->screenres_y = max_y_res;
}