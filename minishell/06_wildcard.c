/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_wildcard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 18:41:59 by tmura             #+#    #+#             */
/*   Updated: 2025/08/26 13:07:24 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	match_pattern(const char *pattern, const char *str)
{
	while (*pattern && *str)
	{
		if (*pattern == '*')
		{
			pattern++;
			if (*pattern == '\0')
				return (1);
			while (*str)
			{
				if (match_pattern(pattern, str))
					return (1);
				str++;
			}
			return (0);
		}
		else if (*pattern == *str)
		{
			pattern++;
			str++;
		}
		else
			return (0);
	}
	return ((*pattern == '*' && *(pattern + 1) == '\0')
		|| (*pattern == '\0' && *str == '\0'));
}

char	**expand_wildcard_token(const char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**results;
	int				count;
	const char		*filename;

	dir = opendir(".");
	if (!dir)
		return (NULL);
	results = malloc(sizeof(char *) * 100);
	if (!results)
		return (closedir(dir), NULL);
	count = 0;
	entry = readdir(dir);
	while (entry != NULL)
	{
		filename = entry->d_name;
		if (filename[0] != '.' || pattern[0] == '.')
			if (match_pattern(pattern, filename))
				results[count++] = ft_strdup(filename);
		entry = readdir(dir);
	}
	results[count] = NULL;
	closedir(dir);
	return (results);
}

int	contains_wildcard(const char *s)
{
	return (ft_strchr(s, '*') != NULL);
}
