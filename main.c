/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <lwiedijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/19 14:14:26 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/08/25 13:11:30 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx/mlx.h"

void	render_loop(t_maze *blueprint, t_port *port)
{
	t_mlx		mlx;

	init_mlx(&mlx);
	port->mlx = &mlx;
	mlx.mlx = mlx_init();
	check_max_screensize(blueprint, mlx);
	read_textures(port, blueprint, port->tex);
	mlx.win = mlx_new_window(mlx.mlx, blueprint->screenres_x,
			blueprint->screenres_y, "cub3D");
	mlx_do_key_autorepeatoff(mlx.mlx);
	mlx_hook(mlx.win, 17, 1L << 17, &x_button_hook, port);
	mlx_hook(mlx.win, 2, 1L << 0, &key_press_hook, port);
	mlx_hook(mlx.win, 3, 0, &key_release_hook, port);
	port->mlx->img_1 = mlx_new_image(port->mlx->mlx,
			port->blueprint->screenres_x, port->blueprint->screenres_y);
	port->mlx->addr = mlx_get_data_addr(port->mlx->img_1,
			&port->mlx->bits_per_pixel, &port->mlx->line_length,
			&port->mlx->endian);
	mlx_loop_hook(mlx.mlx, &render_frame, port);
	mlx_loop(mlx.mlx);
}

int	main(int ac, char **av)
{
	t_port		port;
	t_maze		blueprint;
	t_player	player;
	t_rays		rays;
	t_tex		tex;

	init_player(&player);
	init_maze(&blueprint);
	init_tex(&tex);
	port.blueprint = &blueprint;
	port.player = &player;
	port.tex = &tex;
	check_argument(&port, ac, av[1]);
	parse(av[1], &blueprint, &port);
	check_screenres(&blueprint);
	if (!blueprint.map_y)
		ft_error(MISSING_MAP, &port);
	set_player(&port);
	init_rays(&rays, &blueprint);
	port.rays = &rays;
	render_loop(&blueprint, &port);
}
