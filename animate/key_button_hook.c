/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   key_button_hook.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <lwiedijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/05 14:00:59 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/04/17 09:59:49 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../mlx/mlx.h"
#include <stdlib.h>
#include <stdio.h>

int		x_button_hook(t_mlx *mlx)
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
		exit (0);
	}
	if (keycode == 13)//w
	{
		port->player->pos_y -= 1;
	}
	if (keycode == 1)//s
	{
		port->player->pos_y += 1;
	}
	if (keycode == 0)//a
	{
		port->player->pos_x -= 1;
	}
	if (keycode == 2)//d
	{
		port->player->pos_x += 1;
	}
	port->mlx->on_off = 1;
	return (0);
}