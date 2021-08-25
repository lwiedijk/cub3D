/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_read.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <lwiedijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/20 12:22:08 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/08/25 09:42:40 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

static void	read_error(int	error_code)
{
	if (error_code == MALLOC_FAIL)
		printf("Error\n!malloc fail!\n");
	if (error_code == INVALID_FD)
		printf("Error\n!invalid fd!\n");
	if (error_code == READ_FAIL)
		printf("Error\n!read failed!\n");
	printf("Exiting program, please adjust input and reboot...\n");
	exit(1);
}

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
		read_error(INVALID_FD);
	while (bytes_read)
	{
		countstring = (char *)malloc(sizeof(char) * *buffer_size);
		if (!countstring)
			read_error(MALLOC_FAIL);
		bytes_read = read(fd, countstring, *buffer_size);
		if (bytes_read < 0)
			read_error(READ_FAIL);
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
		read_error(INVALID_FD);
	mapfile = (char *)malloc(sizeof(char) * (buffer_size + 1));
	if (!mapfile)
		read_error(MALLOC_FAIL);
	bytes_read = read(fd, mapfile, buffer_size);
	if (bytes_read < 0)
		read_error(READ_FAIL);
	mapfile[bytes_read] = '\0';
	mapfile[bytes_read + 1] = '\0';
	close(fd);
	return (mapfile);
}
