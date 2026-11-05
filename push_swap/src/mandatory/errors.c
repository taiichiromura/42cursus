/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 11:09:03 by tmura             #+#    #+#             */
/*   Updated: 2025/07/12 11:30:08 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	error_exit(t_list_ps **stack)
{
	free_stack(stack);
	write(2, "Error\n", 6);
	exit(1);
}

void	handle_error(char *line, t_list_ps **stack_a, t_list_ps **stack_b)
{
	free(line);
	free_stack(stack_a);
	free_stack(stack_b);
	write(2, "Error\n", 6);
	exit(1);
}
