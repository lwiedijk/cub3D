/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_textures.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/24 15:14:13 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/07/22 08:31:17 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx/mlx.h"
#include "libft/libft.h"
#include <stdlib.h>

void	free_texture_path(t_maze *blueprint)
{
	free(blueprint->north_texture);
	free(blueprint->east_texture);
	free(blueprint->south_texture);
	free(blueprint->west_texture);
}

void	read_next_textures(t_port *port, t_maze *blueprint, t_tex *tex)
{
	tex->tex_array[2].tex_pnt = mlx_xpm_file_to_image(port->mlx->mlx,
			blueprint->south_texture, &tex->tex_array[2].tex_width,
			&tex->tex_array[2].tex_hight);
	tex->tex_array[2].tex_addr = mlx_get_data_addr(tex->tex_array[2].tex_pnt,
			&tex->tex_array[2].tex_bpp, &tex->tex_array[2].tex_ls,
			&tex->tex_array[2].tex_endian);
	tex->tex_array[3].tex_pnt = mlx_xpm_file_to_image(port->mlx->mlx,
			blueprint->west_texture, &tex->tex_array[3].tex_width,
			&tex->tex_array[3].tex_hight);
	tex->tex_array[3].tex_addr = mlx_get_data_addr(tex->tex_array[3].tex_pnt,
			&tex->tex_array[3].tex_bpp, &tex->tex_array[3].tex_ls,
			&tex->tex_array[3].tex_endian);
	free_texture_path(blueprint);
}

void	read_textures(t_port *port, t_maze *blueprint, t_tex *tex)
{
	tex->tex_array = (t_tex_array *)malloc(sizeof(t_tex_array) * 4);
	if (!tex->tex_array)
		ft_error(MALLOC_FAIL);
	tex->tex_array[0].tex_pnt = mlx_xpm_file_to_image(port->mlx->mlx,
			blueprint->north_texture, &tex->tex_array[0].tex_width,
			&tex->tex_array[0].tex_hight);
	tex->tex_array[0].tex_addr = mlx_get_data_addr(tex->tex_array[0].tex_pnt,
			&tex->tex_array[0].tex_bpp, &tex->tex_array[0].tex_ls,
			&tex->tex_array[0].tex_endian);
	tex->tex_array[1].tex_pnt = mlx_xpm_file_to_image(port->mlx->mlx,
			blueprint->east_texture, &tex->tex_array[1].tex_width,
			&tex->tex_array[1].tex_hight);
	tex->tex_array[1].tex_addr = mlx_get_data_addr(tex->tex_array[1].tex_pnt,
			&tex->tex_array[1].tex_bpp, &tex->tex_array[1].tex_ls,
			&tex->tex_array[1].tex_endian);
	read_next_textures(port, blueprint, tex);
}
