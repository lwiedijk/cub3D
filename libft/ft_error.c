/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_error.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <lwiedijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/20 12:30:28 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/07/09 11:30:16 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

void	ft_error(int error_code)
{
	if (error_code == 1)
		write(1, "Error, not a valid cub-file!\n", 29);
	if (error_code == 2)
		write(1, "Error, malloc fail!\n", 20);
	if (error_code == 3)
		write(1, "Error, invalid fd!\n", 19);
	if (error_code == 4)
		write(1, "Error, read failed!\n", 20);
	if (error_code == 5)
		write(1, "Error, wrong amound of arguments!\n", 34);
	if (error_code == 6)
		write(1, "Error, invalid map!\n", 20);
	write(1, "Exiting program, please reboot...\n", 34);
	exit(1);
}
