/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_error.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <lwiedijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/20 12:30:28 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/07/28 11:50:23 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "cub3d.h"

void	ft_error(int error_code)
{
	if (error_code == INCORRECT_CUB_FILE)
	{
		printf("Error\n!not a valid cub-file!\n");
		printf("illegal, missing or wrong order of elements!\n");
	}
	if (error_code == MALLOC_FAIL)
		printf("Error\n!malloc fail!\n");
	if (error_code == INVALID_FD)
		printf("Error\n!invalid fd!\n");
	if (error_code == READ_FAIL)
		printf("Error\n!read failed!\n");
	if (error_code == WRONG_ARGC)
		printf("Error\n!wrong amound of arguments!\n");
	if (error_code == INVALID_MAP)
		printf("Error\n!invalid map!\n");
	if (error_code == MISSING_MAP)
		printf("Error\n!No map is provided!\n");
	if (error_code == TOO_MANY_ELEMENTS)
		printf("Error\n!Too many elements provided!\n");
	if (error_code == TOO_MANY_PLAYERS)
		printf("Error\n!Only one player is allowed in the map!\n");
	if (error_code == NOT_ALL_ELEMENTS)
		printf("Error\n!Not all necessary elements are provided!\n");
	if (error_code == NO_NUMBER)
		printf("Error\n!Two positive numbers must be entered for screensize!\n");
	if (error_code == ILLEGAL_CHAR)
		printf("Error\n!That character is not allowed at this spot!\n");
	if (error_code == BAD_NUM_RANGE)
		printf("Error\n!A number between 0 and 255 must be entered here!\n");
	if (error_code == NO_COMMA)
		printf("Error\n!Color needs to be separated by comma and comma only!\n");
	if (error_code == INVALID_PATH)
		printf("Error\n!This Texture-path is not valid!\n");
	printf("Exiting program, please adjust input and reboot...\n");
	exit(1);
}
