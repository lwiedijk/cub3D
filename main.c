/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <lwiedijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/19 14:14:26 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/04/30 16:49:05 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx/mlx.h"
#include <stdio.h>

void	set_player(t_port *port)
{
	int		x;
	int 	y;

	x = 0;
	y = 0;
	while(y < port->blueprint->map_y)
	{
		x = 0;
		while (x < port->blueprint->map_x[y])
		{
			if (port->blueprint->map[y][x] == 'p')//player
			{
				port->player->pos_x = (x * 20);
				port->player->pos_y = (y * 20);
			}
			x++;
		}
		y++;
	}
}

void	render_loop(t_maze *blueprint, t_mlx *mlx, t_port *port)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, blueprint->screenres_x, blueprint->screenres_y, "cub3D");
	mlx_hook(mlx->win, 17, 1L<<17, &x_button_hook, mlx);
	mlx_hook(mlx->win, 2, 1L<<0, &key_press_hook, port);
	mlx_hook(mlx->win, 3, 0, &key_release_hook, port);
	mlx_loop_hook(mlx->mlx, render_frame, port);
	mlx_loop(mlx->mlx);
}

int	main(int ac, char **av)
{
	t_port	port;
	t_maze	blueprint;
	t_mlx	mlx;
	t_player	player;

	init_player(&player);
	init_maze(&blueprint);
	init_mlx(&mlx);
	port.blueprint = &blueprint;
	port.mlx = &mlx;
	port.player = &player;
	parse(av[1], &blueprint);
	set_player(&port);
	render_loop(&blueprint, &mlx, &port);

}
