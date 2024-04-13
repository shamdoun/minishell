/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 21:44:21 by shamdoun          #+#    #+#             */
/*   Updated: 2023/11/05 21:46:16 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	size_t	nbr;

	if (fd < 0)
		return ;
	nbr = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		nbr = -nbr;
	}
	if (nbr < 10)
		ft_putchar_fd(nbr + '0', fd);
	else
	{
		ft_putnbr_fd(nbr / 10, fd);
		ft_putnbr_fd(nbr % 10, fd);
	}
}

// #include <fcntl.h>
// #include <stdio.h>
// int main()
// {
// 	// int fd = open("hello",O_RDWR | O_CREAT);
// 	// // ft_putnbr_fd(2,fd);
// 	// // ft_putendl_fd("hellodseihiubib biulbjhbl jllhjbh",fd);
// 	// char c[25];
// 	// read(fd,c,sizeof(int));
// 	// printf("line %s",c);
// 	// close(fd);
// }
