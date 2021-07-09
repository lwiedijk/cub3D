/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   key_button_hook.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <lwiedijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/05 14:00:59 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/07/09 16:39:03 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../mlx/mlx.h"
#include <stdlib.h>
#include <stdio.h>

int	x_button_hook(t_mlx *mlx)
{
	printf("%s\n", "x_button pressed, Terminating program...");
	exit(0);
	mlx->on_off = 1;
	return (0);
}

int	key_press_hook(int keycode, t_port *port)
{
	if (keycode == 53)
	{
		printf("%s\n", "esc is pressed, Terminating program...");
		mlx_destroy_window(port->mlx->mlx, port->mlx->win);
		//free(blueprint->map_x); which is a 2d array with the count for x on each y
		//free(map[y][x]); which is a 2d array with the actual map


		//mlx_destroy_image(port->mlx->mlx, port->mlx->img_1);
		// or is it img_2? which one is active?



		//system("leaks cub3D");
		exit (0);
	}
	if (keycode == 13)
		port->player->walkdirection = 1;
	if (keycode == 1)
		port->player->walkdirection = -1;
	if (keycode == 0)
		port->player->strafe = 1;
	if (keycode == 2)
		port->player->strafe = -1;
	if (keycode == 124)
		port->player->turndirection = 1;
	if (keycode == 123)
		port->player->turndirection = -1;
	port->mlx->on_off = 1;
	return (0);
}

int	key_release_hook(int keycode, t_port *port)
{
	if (keycode == 13)
		port->player->walkdirection = 0;
	if (keycode == 1)
		port->player->walkdirection = 0;
	if (keycode == 0)
		port->player->strafe = 0;
	if (keycode == 2)
		port->player->strafe = 0;
	if (keycode == 124)
		port->player->turndirection = 0;
	if (keycode == 123)
		port->player->turndirection = 0;
	port->mlx->on_off = 1;
	return (0);
}
