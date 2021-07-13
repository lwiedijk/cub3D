/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_color.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <lwiedijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/19 16:01:24 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/07/13 13:31:33 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"
#include <unistd.h>

void	put_color_blueprint(t_maze *blueprint, char type)
{
	if (type == 'f')
		blueprint->floor_color = ((blueprint->r & 0xff) << 16)
		 + ((blueprint->g & 0xff) << 8) + (blueprint->b & 0xff);
	if (type == 'c')
		blueprint->ceiling_color = ((blueprint->r & 0xff) << 16)
		 + ((blueprint->g & 0xff) << 8) + (blueprint->b & 0xff);
}

void	put_rgb_blueprint(t_maze *blueprint, int rgb_count,
int len, char *mapfile)
{
	if (rgb_count == 1)
	{
		blueprint->r = ft_atoi(&mapfile[blueprint->filepos]);
		blueprint->filepos += len + 1;
		if(blueprint->r > 255 || blueprint->r < 0)
			ft_error(INCORRECT_CUB_FILE);
	}
	if (rgb_count == 2)
	{
		blueprint->g = ft_atoi(&mapfile[blueprint->filepos]);
		blueprint->filepos += len + 1;
		if(blueprint->g > 255 || blueprint->g < 0)
			ft_error(INCORRECT_CUB_FILE);
	}
	if (rgb_count == 3)
	{
		blueprint->b = ft_atoi(&mapfile[blueprint->filepos]);
		blueprint->filepos += len;
		if(blueprint->b > 255 || blueprint->b < 0)
			ft_error(INCORRECT_CUB_FILE);
	}
}

void	check_color_input(t_maze *blueprint, char *mapfile)
{
	int	i;
	int	len;
	int rgb_count;
	
	rgb_count = 0;
	i = blueprint->filepos;
	while (mapfile[i] != ' ' && !(mapfile[i] > 8 && mapfile[i] < 14))
	{	
		len = 0;
		while (ft_isdigit(mapfile[i]))
		{
			len++;
			i++;
		}
		rgb_count++;
		put_rgb_blueprint(blueprint, rgb_count, len, mapfile);
		if(rgb_count <= 2 && mapfile[i] != ',')
			ft_error(INCORRECT_CUB_FILE);
		if(len > 3 || rgb_count > 3)
			ft_error(INCORRECT_CUB_FILE);
		if(rgb_count == 3)
			continue;
		i++;
	}
}

void	parse_color(t_maze *blueprint, char *mapfile, char type)
{
	blueprint->filepos++;
	while (mapfile[blueprint->filepos] == ' ')
		blueprint->filepos++;
	if (mapfile[blueprint->filepos] < '0' || mapfile[blueprint->filepos] > '9')
		ft_error(INCORRECT_CUB_FILE);
	check_color_input(blueprint, mapfile);
	put_color_blueprint(blueprint, type);
}