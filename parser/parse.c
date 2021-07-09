/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <lwiedijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/19 14:29:17 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/07/09 11:28:44 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>

void	parse_cubfile(t_maze *blueprint, char *mapfile)
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
	else if (mapfile[blueprint->filepos] == 'F')
		parse_color(blueprint, mapfile, 'f');
	else if (mapfile[blueprint->filepos] == 'C')
		parse_color(blueprint, mapfile, 'c');
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
		ft_error(INCORRECT_CUB_FILE);
	while (mapfile[blueprint->filepos] == '\n')
			blueprint->filepos++;
	
}

int	cubfile_read_is_complete(t_maze *blueprint)
{
	if (blueprint->screenres_x && blueprint->screenres_y && blueprint->north_texture
		&& blueprint->south_texture && blueprint->east_texture && blueprint->west_texture
		&& blueprint->ceiling_color && blueprint->floor_color)
		return (1);
	else
		return (0);
}

void	parse(char *av, t_maze *blueprint)
{
	char	*mapfile;

	mapfile = ft_read(av);
	while (mapfile[blueprint->filepos] != '\0')
	{
		while (mapfile[blueprint->filepos] == '\n' || mapfile[blueprint->filepos] == ' ')
			blueprint->filepos++;
		parse_cubfile(blueprint, mapfile);
		if (cubfile_read_is_complete(blueprint))
			parse_cubfile_map(blueprint, mapfile);
		if (mapfile[blueprint->filepos] != '\n' && mapfile[blueprint->filepos] != '\0')
			ft_error(INCORRECT_CUB_FILE);
	}
	//system("leaks cub3D");
	//exit(1);
	free(mapfile);
	//mapfile = 0;
	//system("leaks cub3D");
	//mind to free blueprint->map_x!
	write(1, "Blueprint is created successfully!\n", 35);
}
