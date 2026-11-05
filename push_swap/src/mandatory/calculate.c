/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:46:25 by tmura             #+#    #+#             */
/*   Updated: 2025/07/12 11:30:00 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

int	calc_costs(int ra, int rb, int rra, int rrb)
{
	int	c1;
	int	c2;
	int	c3;
	int	c4;

	c1 = max(ra, rb);
	c2 = max(rra, rrb);
	c3 = ra + rrb;
	c4 = rb + rra;
	return (min4(c1, c2, c3, c4));
}

int	select_pattern(t_move m, int cost)
{
	int	costs[4];

	costs[0] = max(m.ra, m.rb);
	costs[1] = max(m.rra, m.rrb);
	costs[2] = m.ra + m.rrb;
	costs[3] = m.rb + m.rra;
	if (cost == costs[0])
		return (1);
	else if (cost == costs[1])
		return (2);
	else if (cost == costs[2])
		return (3);
	return (4);
}

t_cheap	update_best(t_best_ctx ctx, t_cheap best)
{
	t_move	mv;
	int		cost;
	int		pat;

	mv.ra = find_position_b(ctx.a, ctx.b);
	mv.rb = ctx.idx;
	mv.rra = ctx.size_a - mv.ra;
	mv.rrb = ctx.size_b - ctx.idx;
	cost = calc_costs(mv.ra, mv.rb, mv.rra, mv.rrb);
	pat = select_pattern(mv, cost);
	if (cost < best.cost)
	{
		best.idx = ctx.idx;
		best.ra = mv.ra;
		best.rb = mv.rb;
		best.pat = pat;
		best.cost = cost;
		best.node = ctx.a;
	}
	return (best);
}

t_cheap	calculate(t_list_ps *stack_a, t_list_ps *stack_b)
{
	t_best_ctx	ctx;
	t_cheap		best;

	ctx.a = stack_a;
	ctx.b = stack_b;
	ctx.size_b = count_lists(stack_a);
	ctx.size_a = count_lists(stack_b);
	ctx.idx = 0;
	best.cost = INT_MAX;
	while (ctx.a)
	{
		best = update_best(ctx, best);
		if (best.cost == 1)
			break ;
		ctx.a = ctx.a->next;
		ctx.idx++;
	}
	return (best);
}
