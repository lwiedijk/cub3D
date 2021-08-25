/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <lwiedijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/19 14:29:17 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/08/25 09:42:24 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>

int	parse_cubfile_nextpart_two(t_maze *blueprint, char *mapfile, t_port *port)
{
	if (mapfile[blueprint->filepos] == 'E'
		&& mapfile[blueprint->filepos + 1] == 'A')
	{
		if (blueprint->east_texture)
			ft_error(TOO_MANY_ELEMENTS, port);
		parse_textures(blueprint, mapfile, 'E', port);
		return (1);
	}
	else if (mapfile[blueprint->filepos] == 'W'
		&& mapfile[blueprint->filepos + 1] == 'E')
	{
		if (blueprint->west_texture)
			ft_error(TOO_MANY_ELEMENTS, port);
		parse_textures(blueprint, mapfile, 'W', port);
		return (1);
	}
	else if (mapfile[blueprint->filepos] == 'S')
		ft_error(NO_SPRITE, port);
	return (0);
}

int	parse_cubfile_nextpart(t_maze *blueprint, char *mapfile, t_port *port)
{
	if (mapfile[blueprint->filepos] == 'F')
	{
		if (blueprint->floor_color != -1)
			ft_error(TOO_MANY_ELEMENTS, port);
		parse_color(blueprint, mapfile, 'f', port);
		return (1);
	}
	else if (mapfile[blueprint->filepos] == 'C')
	{
		if (blueprint->ceiling_color != -1)
			ft_error(TOO_MANY_ELEMENTS, port);
		parse_color(blueprint, mapfile, 'c', port);
		return (1);
	}
	else if (mapfile[blueprint->filepos] == 'R')
	{
		parse_screenres(blueprint, mapfile, port);
		return (1);
	}
	else if (parse_cubfile_nextpart_two(blueprint, mapfile, port))
		return (1);
	return (0);
}

void	parse_cubfile(t_maze *blueprint, char *mapfile, t_port *port)
{
	if (mapfile[blueprint->filepos] == 'N'
		&& mapfile[blueprint->filepos + 1] == 'O')
	{
		if (blueprint->north_texture)
			ft_error(TOO_MANY_ELEMENTS, port);
		parse_textures(blueprint, mapfile, 'N', port);
	}
	else if (mapfile[blueprint->filepos] == 'S'
		&& mapfile[blueprint->filepos + 1] == 'O')
	{
		if (blueprint->south_texture)
			ft_error(TOO_MANY_ELEMENTS, port);
		parse_textures(blueprint, mapfile, 'S', port);
	}
	else if (parse_cubfile_nextpart(blueprint, mapfile, port))
		return ;
	else
		ft_error(INCORRECT_CUB_FILE, port);
}

void	parse_cubfile_map(t_maze *blueprint, char *mapfile, t_port *port)
{
	while (mapfile[blueprint->filepos] == '\n')
		blueprint->filepos++;
	if (mapfile[blueprint->filepos] == ' '
		|| mapfile[blueprint->filepos] == '1')
		parse_map(blueprint, mapfile, port);
	else if (mapfile[blueprint->filepos] == '\0')
		ft_error(MISSING_MAP, port);
	else
		ft_error(TOO_MANY_ELEMENTS, port);
	while (mapfile[blueprint->filepos] == '\n')
		blueprint->filepos++;
}

void	parse(char *av, t_maze *blueprint, t_port *port)
{
	blueprint->mapfile = ft_read(av);
	while (blueprint->mapfile[blueprint->filepos] != '\0')
	{
		while (blueprint->mapfile[blueprint->filepos] == '\n'
			|| blueprint->mapfile[blueprint->filepos] == ' ')
			blueprint->filepos++;
		parse_cubfile(blueprint, blueprint->mapfile, port);
		if (cubfile_read_is_complete(blueprint, blueprint->mapfile))
			parse_cubfile_map(blueprint, blueprint->mapfile, port);
		if (blueprint->mapfile[blueprint->filepos] != '\0'
			&& blueprint->mapfile[blueprint->filepos] != '\n')
			ft_error(READ_FAIL, port);
	}
	free(blueprint->mapfile);
	blueprint->mapfile = NULL;
	write(1, "Blueprint is created successfully!\n", 35);
}
