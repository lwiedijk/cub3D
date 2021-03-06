/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_textures.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <lwiedijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/19 15:47:23 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/08/25 11:58:27 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void	check_texture(char *path, int len, t_port *port)
{
	int	fd;

	fd = 0;
	if (path[len - 4] != '.' || path [len - 3] != 'x')
		ft_error(INVALID_PATH, port);
	fd = open(path, O_RDONLY);
	if (fd > 0)
		close(fd);
	else
		ft_error(INVALID_PATH, port);
}

char	*copy_path_from_mapfile(t_maze *blueprint, char *mapfile,
	int len, t_port *port)
{
	char	*path;
	char	*temp;

	path = (char *)malloc(sizeof(char) * len + 1);
	if (!path)
		ft_error(MALLOC_FAIL, port);
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

void	parse_textures(t_maze *blueprint, char *mapfile,
	char texture_type, t_port *port)
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
	path = copy_path_from_mapfile(blueprint, mapfile, len, port);
	check_texture(path, len, port);
	put_path_to_blueprint(blueprint, texture_type, path);
	while (mapfile[blueprint->filepos] == ' '
		&& mapfile[blueprint->filepos] != '\n')
		blueprint->filepos++;
}
