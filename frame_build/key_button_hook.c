/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   key_button_hook.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <lwiedijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/05 14:00:59 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/07/22 09:39:23 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../mlx/mlx.h"
#include <stdlib.h>
#include <stdio.h>

void	free_map(t_maze *blueprint)
{
	int	i;

	i = 0;
	free(blueprint->map_x);
	while (i < blueprint->map_y)
	{
		free(blueprint->map[i]);
		i++;
	}
	free(blueprint->map);
}

void	free_texture_array(t_port *port, t_tex *textures)
{
	int	i;

	i = 0;
	while (i < TEX_ARRAY_SIZE)
	{
		mlx_destroy_image(port->mlx->mlx, textures->tex_array[i].tex_pnt);
		i++;
	}
	free(textures->tex_array);
}

int	x_button_hook(t_port *port)
{
	free_texture_array(port, port->tex);
	free_map(port->blueprint);
	mlx_destroy_image(port->mlx->mlx, port->mlx->img_1);
	mlx_destroy_window(port->mlx->mlx, port->mlx->win);
	printf("%s\n", "!x_button pressed, Program is terminated!");
	exit(0);
	return (0);
}

int	key_press_hook(int keycode, t_port *port)
{
	if (keycode == ESC_KEY)
	{
		free_texture_array(port, port->tex);
		free_map(port->blueprint);
		mlx_destroy_image(port->mlx->mlx, port->mlx->img_1);
		mlx_destroy_window(port->mlx->mlx, port->mlx->win);
		printf("%s\n", "!Esc is pressed, Program is terminated!");
		exit(0);
	}
	if (keycode == W_KEY)
		port->player->walkdirection = 1;
	if (keycode == S_KEY)
		port->player->walkdirection = -1;
	if (keycode == A_KEY)
		port->player->strafe = 1;
	if (keycode == D_KEY)
		port->player->strafe = -1;
	if (keycode == RIGHT_ARROW)
		port->player->turndirection = 1;
	if (keycode == LEFT_ARROW)
		port->player->turndirection = -1;
	return (0);
}

int	key_release_hook(int keycode, t_port *port)
{
	if (keycode == W_KEY)
		port->player->walkdirection = 0;
	if (keycode == S_KEY)
		port->player->walkdirection = 0;
	if (keycode == A_KEY)
		port->player->strafe = 0;
	if (keycode == D_KEY)
		port->player->strafe = 0;
	if (keycode == RIGHT_ARROW)
		port->player->turndirection = 0;
	if (keycode == LEFT_ARROW)
		port->player->turndirection = 0;
	return (0);
}
