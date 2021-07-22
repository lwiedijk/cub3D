/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_read.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <lwiedijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/20 12:22:08 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/07/22 13:20:10 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

static void	get_buffer_size(char *filename, int *buffer_size)
{
	int		fd;
	int		bytes_read;
	int		count_filebytes;
	char	*countstring;

	bytes_read = 1;
	count_filebytes = 1;
	*buffer_size = 100;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_error(INVALID_FD);
	while (bytes_read)
	{
		countstring = (char *)malloc(sizeof(char) * *buffer_size);
		if (!countstring)
			ft_error(MALLOC_FAIL);
		bytes_read = read(fd, countstring, *buffer_size);
		if (bytes_read < 0)
			ft_error(READ_FAIL);
		free(countstring);
		count_filebytes = count_filebytes + bytes_read;
	}
	*buffer_size = count_filebytes;
	close(fd);
}

char	*ft_read(char *filename)
{
	char	*mapfile;
	int		fd;
	int		bytes_read;
	int		buffer_size;

	get_buffer_size(filename, &buffer_size);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_error(INVALID_FD);
	mapfile = (char *)malloc(sizeof(char) * buffer_size);
	if (!mapfile)
		ft_error(MALLOC_FAIL);
	bytes_read = read(fd, mapfile, buffer_size);
	if (bytes_read < 0)
		ft_error(READ_FAIL);
	mapfile[bytes_read] = '\0';
	close(fd);
	return (mapfile);
}
