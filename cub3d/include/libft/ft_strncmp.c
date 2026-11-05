/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:43:51 by tmura             #+#    #+#             */
/*   Updated: 2025/05/05 18:48:00 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1 && s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
/*
#include <string.h>
#include <stdio.h>
int	main(void)
{
	const char *tests[][2] = {
		{"abc", "abc"},
		{"abc", "abd"},
		{"abc", "abcd"},
		{"abcd", "abc"},
		{"", ""},
		{"a", ""},
		{"", "a"},
		{"abc", "ABC"},
		{"abcdef", "abcxyz"},
	};

	size_t ns[] = {0, 1, 2, 3, 4, 5, 6};
	int num_tests = sizeof(tests) / sizeof(tests[0]);
	int num_ns = sizeof(ns) / sizeof(ns[0]);

	for (int i = 0; i < num_tests; i++)
	{
		for (int j = 0; j < num_ns; j++)
		{
			const char *s1 = tests[i][0];
			const char *s2 = tests[i][1];
			size_t n = ns[j];
			int std = strncmp(s1, s2, n);
			int mine = ft_strncmp(s1, s2, n);
			if ((std == 0 && mine != 0)
			|| (std < 0 && mine >= 0) || (std > 0 && mine <= 0))
			{
				printf("Mismatch for s1=\"%s\",
				s2=\"%s\", n=%zu: strncmp=%d, ft_strncmp=%d\n",
					s1, s2, n, std, mine);
			}
		}
	}
	return (0);
}
*/
