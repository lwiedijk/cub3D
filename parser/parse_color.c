/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_color.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <lwiedijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/19 16:01:24 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/08/24 16:00:03 by lwiedijk      ########   odam.nl         */
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

void	put_rgb_blueprint(t_port *port, int rgb_count,
int len, char *mapfile)
{
	if (rgb_count == 1)
	{
		port->blueprint->r = ft_atoi(&mapfile[port->blueprint->filepos]);
		port->blueprint->filepos += len + 1;
		if (port->blueprint->r > 255 || port->blueprint->r < 0)
			ft_error(BAD_NUM_RANGE, port);
	}
	if (rgb_count == 2)
	{
		port->blueprint->g = ft_atoi(&mapfile[port->blueprint->filepos]);
		port->blueprint->filepos += len + 1;
		if (port->blueprint->g > 255 || port->blueprint->g < 0)
			ft_error(BAD_NUM_RANGE, port);
	}
	if (rgb_count == 3)
	{
		port->blueprint->b = ft_atoi(&mapfile[port->blueprint->filepos]);
		port->blueprint->filepos += len;
		if (port->blueprint->b > 255 || port->blueprint->b < 0)
			ft_error(BAD_NUM_RANGE, port);
	}
}

void	check_color_input(t_maze *blueprint, char *mapfile, t_port *port)
{
	int	i;
	int	len;
	int	rgb_count;

	rgb_count = 0;
	i = blueprint->filepos;
	while (!ft_iswhitespace(mapfile[i]))
	{
		len = 0;
		while (ft_isdigit(mapfile[i]))
		{
			len++;
			i++;
		}
		rgb_count++;
		put_rgb_blueprint(port, rgb_count, len, mapfile);
		if (rgb_count <= 2 && mapfile[i] != ',')
			ft_error(NO_COMMA, port);
		if (len > 3 || rgb_count > 3)
			ft_error(TOO_MANY_ELEMENTS, port);
		if (rgb_count == 3)
			break ;
		i++;
	}
}

void	parse_color(t_maze *blueprint, char *mapfile, char type, t_port *port)
{
	blueprint->filepos++;
	while (mapfile[blueprint->filepos] == ' ')
		blueprint->filepos++;
	if (!ft_isdigit(mapfile[blueprint->filepos]))
		ft_error(BAD_NUM_RANGE, port);
	check_color_input(blueprint, mapfile, port);
	while (mapfile[blueprint->filepos] == ' ')
		blueprint->filepos++;
	put_color_blueprint(blueprint, type);
}
