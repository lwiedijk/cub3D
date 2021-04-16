/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <lwiedijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/07 13:29:27 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/03/20 12:33:31 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>

int		ft_isdigit(int argument);
int		ft_isalpha(int c);
char	*ft_itoa_base(long long value, int base, char *hex_case);
char	*ft_itoa_base_unsigned(unsigned long long value, int base,
			char *hex_case);
int		ft_numlen_base(long value, int base);
char	*ft_strjoin_free(char *s1, char const *s2);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strlen(const char *s);
int		ft_power(int nb, int power);
char	*ft_strcpy(char *dest, char *src);
int		ft_atoi(const char *str);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);
char	*ft_read(char *filename);
void	ft_error(int error_code);

#endif
