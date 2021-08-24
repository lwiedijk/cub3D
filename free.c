/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/18 09:46:33 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/08/24 07:25:18 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cub3d.h"
#include "mlx/mlx.h"

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

void	free_texture_path(t_maze *blueprint)
{
	free(blueprint->north_texture);
	free(blueprint->east_texture);
	free(blueprint->south_texture);
	free(blueprint->west_texture);
}

void	free_at_error(t_port *port)
{
	if (port->blueprint->mapfile)
		free(port->blueprint->mapfile);
	if (port->tex->tex_array)
		free_texture_array(port, port->tex);
	if (port->blueprint->map_x)
		free_map(port->blueprint);
	return ;
}
