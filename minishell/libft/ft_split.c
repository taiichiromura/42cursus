/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:40:43 by ktakeru           #+#    #+#             */
/*   Updated: 2025/05/08 14:41:10 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	count;
	int	word_flag;

	count = 0;
	word_flag = 0;
	while (*s)
	{
		if (*s != c && word_flag == 0)
		{
			word_flag = 1;
			count++;
		}
		else if (*s == c)
			word_flag = 0;
		s++;
	}
	return (count);
}

static int	word_len(char const *s, char c)
{
	int	len;

	len = 0;
	while (s[len] != '\0' && s[len] != c)
		len++;
	return (len);
}

static void	free_res(char **res, int j)
{
	while (j--)
		free(res[j]);
	free(res);
}

static char	**split_word(char const *s, char c, char **res)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			len = word_len(&s[i], c);
			res[j] = ft_substr(s, i, len);
			if (!res[j])
			{
				free_res(res, j);
				return (NULL);
			}
			j++;
			i += len;
		}
		else
			i++;
	}
	res[j] = NULL;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**res;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	res = (char **)malloc((words + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	res = split_word(s, c, res);
	return (res);
}
// #include <stdio.h>

// int	main(void)
// {
// 	char	*src;
// 	char	c;
// 	char	**res;
// 	int		i;

// 	src = "dog,cat,rabbit,bear,dear,beer";
// 	c = ',';
// 	res = ft_split(src, c);
// 	i = 0;
// 	while (res[i])
// 	{
// 		printf("%s\n", res[i]);
// 		free(res[i]);
// 		i++;
// 	}
// 	free(res);
// 	return (0);
// }
