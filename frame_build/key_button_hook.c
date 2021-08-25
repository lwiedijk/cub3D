/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   key_button_hook.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <lwiedijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/05 14:00:59 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/08/25 11:48:23 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../mlx/mlx.h"
#include <stdlib.h>
#include <stdio.h>

int	x_button_hook(t_port *port)
{
	free_texture_array(port, port->tex);
	free_map(port->blueprint);
	mlx_destroy_image(port->mlx->mlx, port->mlx->img_1);
	mlx_destroy_window(port->mlx->mlx, port->mlx->win);
	printf("!x_button pressed, Program is terminated!\n");
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
		printf("!Esc is pressed, Program is terminated!\n");
		exit(0);
	}
	if (keycode == W_KEY)
		port->player->forward = 1;
	if (keycode == S_KEY)
		port->player->backward = -1;
	if (keycode == A_KEY)
		port->player->strafe_r = 1;
	if (keycode == D_KEY)
		port->player->strafe_l = -1;
	if (keycode == RIGHT_ARROW)
		port->player->turndirection_r = 1;
	if (keycode == LEFT_ARROW)
		port->player->turndirection_l = -1;
	return (0);
}

int	key_release_hook(int keycode, t_port *port)
{
	if (keycode == W_KEY)
		port->player->forward = 0;
	if (keycode == S_KEY)
		port->player->backward = 0;
	if (keycode == A_KEY)
		port->player->strafe_r = 0;
	if (keycode == D_KEY)
		port->player->strafe_l = 0;
	if (keycode == RIGHT_ARROW)
		port->player->turndirection_r = 0;
	if (keycode == LEFT_ARROW)
		port->player->turndirection_l = 0;
	return (0);
}
