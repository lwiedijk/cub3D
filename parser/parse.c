/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <lwiedijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/19 14:29:17 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/07/28 07:22:45 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>

int	parse_cubfile_nextpart_two(t_maze *blueprint, char *mapfile)
{
	if (mapfile[blueprint->filepos] == 'E'
		&& mapfile[blueprint->filepos + 1] == 'A')
	{
		if (blueprint->east_texture)
			ft_error(TOO_MANY_ELEMENTS);
		parse_textures(blueprint, mapfile, 'E');
		return (1);
	}
	else if (mapfile[blueprint->filepos] == 'W'
		&& mapfile[blueprint->filepos + 1] == 'E')
	{
		if (blueprint->west_texture)
			ft_error(TOO_MANY_ELEMENTS);
		parse_textures(blueprint, mapfile, 'W');
		return (1);
	}
	return (0);
}

int	parse_cubfile_nextpart(t_maze *blueprint, char *mapfile)
{
	if (mapfile[blueprint->filepos] == 'F')
	{
		if (blueprint->floor_color != -1)
			ft_error(TOO_MANY_ELEMENTS);
		parse_color(blueprint, mapfile, 'f');
		return (1);
	}
	else if (mapfile[blueprint->filepos] == 'C')
	{
		if (blueprint->ceiling_color != -1)
			ft_error(TOO_MANY_ELEMENTS);
		parse_color(blueprint, mapfile, 'c');
		return (1);
	}
	else if (mapfile[blueprint->filepos] == 'R')
	{
		parse_screenres(blueprint, mapfile);
		return (1);
	}
	else if (parse_cubfile_nextpart_two(blueprint, mapfile))
		return (1);
	return (0);
}

void	parse_cubfile(t_maze *blueprint, char *mapfile)
{
	if (mapfile[blueprint->filepos] == 'N'
		&& mapfile[blueprint->filepos + 1] == 'O')
	{
		if (blueprint->north_texture)
			ft_error(TOO_MANY_ELEMENTS);
		parse_textures(blueprint, mapfile, 'N');
	}
	else if (mapfile[blueprint->filepos] == 'S'
		&& mapfile[blueprint->filepos + 1] == 'O')
	{
		if (blueprint->south_texture)
			ft_error(TOO_MANY_ELEMENTS);
		parse_textures(blueprint, mapfile, 'S');
	}
	else if (parse_cubfile_nextpart(blueprint, mapfile))
		return ;
	else
		ft_error(INCORRECT_CUB_FILE);
}

void	parse_cubfile_map(t_maze *blueprint, char *mapfile)
{
	while (mapfile[blueprint->filepos] == '\n')
		blueprint->filepos++;
	if (mapfile[blueprint->filepos] == ' '
		|| mapfile[blueprint->filepos == '1'])
		parse_map(blueprint, mapfile);
	else
		ft_error(TOO_MANY_ELEMENTS);
	while (mapfile[blueprint->filepos] == '\n')
		blueprint->filepos++;
}

void	parse(char *av, t_maze *blueprint)
{
	char	*mapfile;

	mapfile = ft_read(av);
	while (mapfile[blueprint->filepos] != '\0')
	{
		while (mapfile[blueprint->filepos] == '\n'
			|| mapfile[blueprint->filepos] == ' ')
			blueprint->filepos++;
		parse_cubfile(blueprint, mapfile);
		if (cubfile_read_is_complete(blueprint, mapfile))
			parse_cubfile_map(blueprint, mapfile);
		if (mapfile[blueprint->filepos] != '\n'
			&& mapfile[blueprint->filepos] != '\0')
			ft_error(ILLEGAL_CHAR);
	}
	free(mapfile);
	write(1, "Blueprint is created successfully!\n", 35);
}
