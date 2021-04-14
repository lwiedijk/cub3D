/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_textures.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <lwiedijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/19 15:47:23 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/03/20 17:01:45 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void	put_path_to_blueprint(t_maze *blueprint, char *mapfile, char texture_type, char *path, int len)
{
	char *temp;

	temp = &mapfile[blueprint->filepos];
	ft_strlcpy(path, temp, len + 1);
	blueprint->filepos += len;
	if (texture_type == 'N')
		blueprint->north_texture = path;
	if (texture_type == 'S')
		blueprint->south_texture = path;
	if (texture_type == 'W')
		blueprint->west_texture = path;
	if (texture_type == 'E')
		blueprint->east_texture = path;
	if (texture_type == 's')
		blueprint->sprite = path;
}


void	parse_textures(t_maze *blueprint, char *mapfile, char texture_type)
{
	int	len;
	char *path;

	if (texture_type != 's')
		blueprint->filepos += 2;
	else
		blueprint->filepos++;
	while (mapfile[blueprint->filepos] == ' ')
		blueprint->filepos++;
	len = blueprint->filepos;
	while (mapfile[len] != ' ' && !(mapfile[len] > 8 && mapfile[len] < 14))
		len++;
	len -= blueprint->filepos;
	path = (char *)malloc(sizeof(char) * len + 1);
	put_path_to_blueprint(blueprint, mapfile, texture_type, path, len);
	while (mapfile[blueprint->filepos] == ' '
		&& mapfile[blueprint->filepos] != '\n')
		blueprint->filepos++;
}