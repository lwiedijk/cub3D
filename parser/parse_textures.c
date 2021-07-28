/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_textures.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <lwiedijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/19 15:47:23 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/07/28 13:33:01 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void	check_texture(char *path, int len)
{
	FILE	*path_file;

	path_file = NULL;
	if (path[0] != '.' || path[1] != '/')
		ft_error(INVALID_PATH);
	else if (path[len - 4] != '.' || path [len - 3] != 'x')
		ft_error(INVALID_PATH);
	path_file = fopen(path, "r");
	if (path_file)
		fclose(path_file);
	else
		ft_error(INVALID_PATH);
}

char	*copy_path_from_mapfile(t_maze *blueprint, char *mapfile, int len)
{
	char	*path;
	char	*temp;

	path = (char *)malloc(sizeof(char) * len + 1);
	if (!path)
		ft_error(MALLOC_FAIL);
	temp = &mapfile[blueprint->filepos];
	ft_strlcpy(path, temp, len + 1);
	blueprint->filepos += len;
	return (path);
}

void	put_path_to_blueprint(t_maze *blueprint, char texture_type, char *path)
{
	if (texture_type == 'N')
		blueprint->north_texture = path;
	if (texture_type == 'S')
		blueprint->south_texture = path;
	if (texture_type == 'W')
		blueprint->west_texture = path;
	if (texture_type == 'E')
		blueprint->east_texture = path;
}

void	parse_textures(t_maze *blueprint, char *mapfile, char texture_type)
{
	int		len;
	char	*path;

	blueprint->filepos += 2;
	while (mapfile[blueprint->filepos] == ' ')
		blueprint->filepos++;
	len = blueprint->filepos;
	while (!ft_iswhitespace(mapfile[len]))
		len++;
	len -= blueprint->filepos;
	path = copy_path_from_mapfile(blueprint, mapfile, len);
	check_texture(path, len);
	put_path_to_blueprint(blueprint, texture_type, path);
	while (mapfile[blueprint->filepos] == ' '
		&& mapfile[blueprint->filepos] != '\n')
		blueprint->filepos++;
}
