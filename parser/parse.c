/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <lwiedijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/19 14:29:17 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/04/13 18:32:51 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>

void	parse_mapfile(t_maze *blueprint, char *mapfile)
{
	if (mapfile[blueprint->filepos] == 'R')
		parse_screenres(blueprint, mapfile);
	else if (mapfile[blueprint->filepos] == 'N'
		&& mapfile[blueprint->filepos + 1] == 'O')
		parse_textures(blueprint, mapfile, 'N');
	else if (mapfile[blueprint->filepos] == 'S'
		&& mapfile[blueprint->filepos + 1] == 'O')
		parse_textures(blueprint, mapfile, 'S');
	else if (mapfile[blueprint->filepos] == 'W'
		&& mapfile[blueprint->filepos + 1] == 'E')
		parse_textures(blueprint, mapfile, 'W');
	else if (mapfile[blueprint->filepos] == 'E'
		&& mapfile[blueprint->filepos + 1] == 'A')
		parse_textures(blueprint, mapfile, 'E');
	else if (mapfile[blueprint->filepos] == 'S')
		parse_textures(blueprint, mapfile, 's');
	else if (mapfile[blueprint->filepos] == 'F')
		parse_color(blueprint, mapfile, 'f');
	else if (mapfile[blueprint->filepos] == 'C')
		parse_color(blueprint, mapfile, 'c');
	else if (mapfile[blueprint->filepos] == ' '
	|| mapfile[blueprint->filepos == '1'])
		parse_map(blueprint, mapfile);
}

void	parse(char *av, t_maze *blueprint)
{
	char	*mapfile;

	mapfile = ft_read(av);
	while (mapfile[blueprint->filepos] != '\0')
	{
		parse_mapfile(blueprint, mapfile);
		if (mapfile[blueprint->filepos] != '\n' && mapfile[blueprint->filepos] != '\0')
			ft_error(1);
		while (mapfile[blueprint->filepos] == '\n')
			blueprint->filepos++;
	}
	free(mapfile);
	//mind to free blueprint->map_x!
	write(1, "Blueprint is created successfully!\n", 35);
}
