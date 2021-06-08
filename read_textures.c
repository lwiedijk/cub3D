/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_textures.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/24 15:14:13 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/06/08 13:44:37 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"
#include "mlx/mlx.h"
#include "libft/libft.h"
#include <stdlib.h>

void	read_textures(t_port *port, t_maze *blueprint, t_tex *tex)
{
	tex->tex_n = mlx_xpm_file_to_image(port->mlx->mlx, blueprint->north_texture, &tex->x_n, &tex->y_n);
	//free(blueprint->north_texture);
	//if (!tex->tex_n)
	//ft_error(2);
	tex->addr_n = mlx_get_data_addr(tex->tex_n, &tex->bpp_n, &tex->ls_n, &tex->end_n);
	tex->tex_e = mlx_xpm_file_to_image(port->mlx->mlx, blueprint->east_texture, &tex->x_e, &tex->y_e);
	tex->addr_e = mlx_get_data_addr(tex->tex_e, &tex->bpp_e, &tex->ls_e, &tex->end_e);
	tex->tex_s = mlx_xpm_file_to_image(port->mlx->mlx, blueprint->south_texture, &tex->x_s, &tex->y_s);
	tex->addr_s = mlx_get_data_addr(tex->tex_s, &tex->bpp_s, &tex->ls_s, &tex->end_s);
	tex->tex_w = mlx_xpm_file_to_image(port->mlx->mlx, blueprint->west_texture, &tex->x_w, &tex->y_w);
	tex->addr_w = mlx_get_data_addr(tex->tex_w, &tex->bpp_w, &tex->ls_w, &tex->end_w);
}

void	calculate_textures(t_port *port, t_tex *tex, char map)
{
	if (map == 'N')
	{
		tex->step = 1.0 * tex->y_n / port->rays->wall_striphight;
		tex->position = (port->rays->draw_start - port->blueprint->screenres_y / 2 + port->rays->wall_striphight / 2) * tex->step;
	}
	if (map == 'E')
	{
		tex->step = 1.0 * tex->y_e / port->rays->wall_striphight;
		tex->position = (port->rays->draw_start - port->blueprint->screenres_y / 2 + port->rays->wall_striphight / 2) * tex->step;	
	}
	if (map == 'S')
	{
		tex->step = 1.0 * tex->y_s / port->rays->wall_striphight;
		tex->position = (port->rays->draw_start - port->blueprint->screenres_y / 2 + port->rays->wall_striphight / 2) * tex->step;
	}
	if (map == 'W')
	{
		tex->step = 1.0 * tex->y_w / port->rays->wall_striphight;
		tex->position = (port->rays->draw_start - port->blueprint->screenres_y / 2 + port->rays->wall_striphight / 2) * tex->step;
	}	
}

