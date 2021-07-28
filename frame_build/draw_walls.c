/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_walls.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/19 16:22:35 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/07/28 13:42:07 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"
#include "../mlx/mlx.h"
#include <math.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

void	put_cur_texture(t_port *port, t_tex_array tex_array,
		t_rays *rays, int colum_id)
{
	int	tex_color;
	int	y;

	if (port->wall_array[colum_id].vertical_hit)
		port->tex->tex_ofset_x = (int)(port->wall_array[colum_id].wall_hit_y
				* tex_array.tex_width / TILE_SIZE) % tex_array.tex_width;
	else
		port->tex->tex_ofset_x = (int)(port->wall_array[colum_id].wall_hit_x
				* tex_array.tex_width / TILE_SIZE) % tex_array.tex_width;
	while (rays->draw_start < rays->draw_end)
	{
		y = port->rays->draw_start + (rays->wall_striphight / 2)
			- (port->blueprint->screenres_y / 2);
		port->tex->tex_ofset_y = y * ((float)tex_array.tex_hight
				/ rays->wall_striphight);
		tex_color = *(int *)(tex_array.tex_addr + (port->tex->tex_ofset_y
					* tex_array.tex_ls) + (port->tex->tex_ofset_x
					* (tex_array.tex_bpp / 8)));
		my_mlx_pixel_put(port->mlx, colum_id, rays->draw_start, tex_color);
		rays->draw_start++;
	}
}

void	put_all_textures(t_port *port, t_wall *wall_array, int colum_id)
{
	if (wall_array[colum_id].wall_or == 'N')
		put_cur_texture(port, port->tex->tex_array[0], port->rays, colum_id);
	if (wall_array[colum_id].wall_or == 'E')
		put_cur_texture(port, port->tex->tex_array[1], port->rays, colum_id);
	if (wall_array[colum_id].wall_or == 'S')
		put_cur_texture(port, port->tex->tex_array[2], port->rays, colum_id);
	if (wall_array[colum_id].wall_or == 'W')
		put_cur_texture(port, port->tex->tex_array[3], port->rays, colum_id);
}

void	draw_walls(t_port *port, t_rays *rays,
		t_wall *wall_array, int colum_id)
{
	float	distance_to_plane;

	if (colum_id > rays->ray_num)
		return ;
	distance_to_plane = (port->blueprint->screenres_x / 2)
		/ tan(rays->fov_angle / 2);
	rays->wall_striphight = (TILE_SIZE / wall_array[colum_id].raydistance)
		* distance_to_plane;
	rays->draw_start = (port->blueprint->screenres_y / 2)
		- (rays->wall_striphight / 2);
	rays->draw_end = rays->draw_start + rays->wall_striphight;
	if (rays->wall_striphight > port->blueprint->screenres_y)
	{
		rays->draw_end = port->blueprint->screenres_y;
		rays->draw_start = 0;
	}
	put_all_textures(port, wall_array, colum_id);
}
