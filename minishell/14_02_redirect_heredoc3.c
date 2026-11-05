/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   14_02_redirect_heredoc3.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 19:57:11 by ktakeru           #+#    #+#             */
/*   Updated: 2025/09/15 19:59:15 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quotes(const char *str)
{
	char	*result;
	size_t	i;
	size_t	j;

	if (!str)
		return (NULL);
	result = (char *)malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	ft_bzero(result, ft_strlen(str) + 1);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '"')
		{
			result[j] = str[i];
			j++;
		}
		i++;
	}
	return (result);
}

int	is_quoted(const char *delimiter)
{
	if (ft_strchr(delimiter, '\'') || ft_strchr(delimiter, '"'))
		return (1);
	return (0);
}

static char	*get_env_value(char *name, char **envp)
{
	int	len;
	int	i;

	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], name, len) && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

static char	*get_expanded_token(const char *line, int *index, char **envp,
		t_shell_context *context)
{
	char	*var_name;
	char	*var_value;
	int		start;

	(*index)++;
	if (line[*index] == '?')
	{
		(*index)++;
		return (ft_itoa(context->last_exit_status));
	}
	start = *index;
	while (line[*index] && (ft_isalnum(line[*index]) || line[*index] == '_'))
		(*index)++;
	var_name = ft_substr(line, start, *index - start);
	if (!*var_name)
	{
		free(var_name);
		return (ft_strdup("$"));
	}
	var_value = get_env_value(var_name, envp);
	free(var_name);
	if (var_value)
		return (ft_strdup(var_value));
	return (ft_strdup(""));
}

char	*expand_env_heredoc(char *line, char **envp, t_shell_context *context)
{
	char	*result;
	char	*token;
	int		i;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
			token = get_expanded_token(line, &i, envp, context);
		else
		{
			token = ft_substr(line, i, 1);
			i++;
		}
		if (!token)
			return (free(result), NULL);
		result = append_value(result, token);
		free(token);
	}
	return (result);
}
