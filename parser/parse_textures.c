/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_textures.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <lwiedijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/19 15:47:23 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/07/13 11:58:51 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

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
	put_path_to_blueprint(blueprint, texture_type, path);
	while (mapfile[blueprint->filepos] == ' '
		&& mapfile[blueprint->filepos] != '\n')
		blueprint->filepos++;
}
