/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_expand_word_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 23:11:07 by tmura             #+#    #+#             */
/*   Updated: 2025/08/26 12:35:09 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	read_name(const char *str, size_t i)
{
	size_t			j;
	unsigned char	character;

	if (!str || !str[i])
		return (0);
	character = (unsigned char)str[i];
	if (!(isalpha(character) || character == '_'))
		return (0);
	j = i + 1;
	while (str[j])
	{
		character = (unsigned char)str[j];
		if (!(isalnum(character) || character == '_'))
			break ;
		j++;
	}
	return (j - i);
}

char	*itoa_status(int n)
{
	char	buf[12];
	int		i;
	long	value;
	int		negative;

	i = 11;
	buf[i] = '\0';
	value = (long)n;
	negative = (value < 0);
	if (value == 0)
		buf[--i] = '0';
	if (value < 0)
		value = -value;
	while (value > 0)
	{
		buf[--i] = '0' + (value % 10);
		value /= 10;
	}
	if (negative)
		buf[--i] = '-';
	return (ft_strdup(buf + i));
}

char	*pushc(char *str, char character)
{
	char	*new_string;
	size_t	len;
	char	tmp[2];

	tmp[0] = character;
	tmp[1] = '\0';
	if (!str)
		return (ft_strdup(tmp));
	len = ft_strlen(str);
	new_string = (char *)malloc(len + 2);
	if (!new_string)
		return (NULL);
	ft_strcpy(new_string, str);
	new_string[len] = character;
	new_string[len + 1] = '\0';
	free(str);
	return (new_string);
}

char	*pushs(char *str, const char *add)
{
	size_t	i;

	i = 0;
	while (add && add[i])
	{
		str = pushc(str, add[i]);
		if (!str)
			return (NULL);
		i++;
	}
	return (str);
}
