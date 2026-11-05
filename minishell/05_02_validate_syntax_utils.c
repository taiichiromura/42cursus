/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_02_validate_syntax_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakeru <ktakeru@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:34:18 by ktakeru           #+#    #+#             */
/*   Updated: 2025/09/18 16:34:43 by ktakeru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir(int t)
{
	return (t == T_REDIR_OUT || t == T_REDIR_APPEND);
}

int	is_op(int t)
{
	return (t == T_PIPE);
}

int	is_cmd_start_token(int type)
{
	return (type == T_WORD || type == T_OPEN_PAREN || is_redir(type));
}
