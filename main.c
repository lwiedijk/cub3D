/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <lwiedijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/19 14:14:26 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/05/12 12:34:36 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx/mlx.h"
#include <stdio.h>

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
	t_port		port;
	t_maze		blueprint;
	t_mlx		mlx;
	t_player	player;
	t_rays		rays;

	init_player(&player);
	init_maze(&blueprint);
	init_mlx(&mlx);
	port.blueprint = &blueprint;
	port.mlx = &mlx;
	port.player = &player;
	parse(av[1], &blueprint);
	set_player(&port);
	init_rays(&rays, &blueprint);
	port.rays = &rays;
	render_loop(&blueprint, &mlx, &port);

}
