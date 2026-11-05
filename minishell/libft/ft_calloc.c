/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:39:15 by ktakeru           #+#    #+#             */
/*   Updated: 2025/05/06 22:02:52 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*ptr;
	size_t			total;
	size_t			i;
	unsigned char	*p;

	total = nmemb * size;
	if (nmemb == 0 || size == 0)
		return (malloc(1));
	if (nmemb != 0 && total / nmemb != size)
		return (NULL);
	ptr = malloc(total);
	if (ptr == NULL)
		return (NULL);
	p = (unsigned char *)ptr;
	i = 0;
	while (i < total)
	{
		p[i] = 0;
		i++;
	}
	return (ptr);
}
// #include <stdio.h>

// int	main(void)
// {
// 	int		*arr;
// 	size_t	nmemb;
// 	size_t	size;
// 	size_t	i;

// 	nmemb = 5;
// 	size = sizeof(int);
// 	arr = (int *)ft_calloc(nmemb, size);
// 	if (!arr)
// 	{
// 		printf("Memory allocation failed.\n");
// 		return (1);
// 	}
// 	i = 0;
// 	while (i < nmemb)
// 	{
// 		printf("arr[%zu] = %d\n", i, arr[i]);
// 		i++;
// 	}
// 	free(arr);
// 	return (0);
// }
