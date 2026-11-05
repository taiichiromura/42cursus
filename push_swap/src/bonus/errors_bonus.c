/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 11:09:03 by tmura             #+#    #+#             */
/*   Updated: 2025/07/12 12:34:10 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap_bonus.h"

void	error_exit(t_list_ps **stack)
{
	free_stack(stack);
	write(2, "Error\n", 6);
	exit(1);
}

void	handle_error(char *line, t_list_ps **a, t_list_ps **b)
{
	free(line);
	free_stack(a);
	free_stack(b);
	write(2, "Error\n", 6);
	exit(1);
}
