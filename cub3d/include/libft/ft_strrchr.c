/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:43:57 by tmura             #+#    #+#             */
/*   Updated: 2025/05/05 18:48:21 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	char			*ptr;
	unsigned char	ch;

	i = 0;
	ptr = 0;
	ch = (unsigned char)c;
	while (s[i])
	{
		if (s[i] == ch)
			ptr = (char *)(s + i);
		i++;
	}
	if (s[i] == ch)
		ptr = (char *)(s + i);
	return (ptr);
}

/*
#include <string.h>
#include <stdio.h>
int main(void)
{
	const char *test_str = "banana";
	int test_char = 'a';

	// 標準関数との比較
	char *libc_result = strrchr(test_str, test_char);
	char *ft_result = ft_strrchr(test_str, test_char);

	printf("Input string: \"%s\"\n", test_str);
	printf("Character to find: '%c'\n", test_char);
	printf("strrchr result:    \"%s\"\n", libc_result);
	printf("ft_strrchr result: \"%s\"\n", ft_result);

	if (libc_result == ft_result)
		printf("✅ Passed: Same pointer returned.\n");
	else if (libc_result && ft_result && strcmp(libc_result, ft_result) == 0)
		printf("✅ Passed: Same string content.\n");
	else
		printf("❌ Failed: Different result.\n");

	return 0;
}
*/
