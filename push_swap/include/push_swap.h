/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 14:10:33 by tmura             #+#    #+#             */
/*   Updated: 2025/07/12 14:10:35 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include "../libft/libft.h"

# define ERROR -1
# define OK 1
# define INIT_CAPACITY 1024

typedef struct s_node
{
	int				value;
	int				keep;
	struct s_node	*next;
}	t_list_ps;

typedef struct cheap
{
	t_list_ps	*node;
	int			cost;
	int			idx;
	int			ra;
	int			rb;
	int			pat;
}	t_cheap;

typedef struct s_lis_data
{
	int		*arr;
	int		*lengths;
	int		*prev;
	int		size;
	int		max_end;
}	t_lis_data;

typedef struct s_mark
{
	int			*indexes;
	int			len;
	int			i;
	int			j;
	t_list_ps	*tmp;
}	t_mark;

typedef struct s_move
{
	int		ra;
	int		rb;
	int		rra;
	int		rrb;
}	t_move;

typedef struct s_best_ctx
{
	t_list_ps	*a;
	t_list_ps	*b;
	int			idx;
	int			size_b;
	int			size_a;
}	t_best_ctx;

typedef struct s_rot
{
	int			na;
	int			nb;
	int			rra_a;
	int			rrb_b;
}	t_rot;

t_list_ps			*new_node(int value);
void				add_back(t_list_ps **head, t_list_ps *new);
int					min_num(t_list_ps *node);
int					max_num(t_list_ps *node);
int					max(int left, int right);
int					min(int left, int right);
int					min4(int a, int b, int c, int d);
void				sa(t_list_ps **a);
void				sb(t_list_ps **b);
void				ss(t_list_ps **a, t_list_ps **b);
void				pa(t_list_ps **a, t_list_ps **b);
void				pb(t_list_ps **a, t_list_ps **b);
void				ra(t_list_ps **a);
void				rb(t_list_ps **b);
void				rr(t_list_ps **a, t_list_ps **b);
void				rra(t_list_ps **a);
void				rrb(t_list_ps **b);
void				rrr(t_list_ps **a, t_list_ps **b);
int					find_position_b(t_list_ps *a, t_list_ps *b);
t_cheap				calculate(t_list_ps *a, t_list_ps *b);
void				execute_move(t_list_ps **a, t_list_ps **b, t_cheap mv);
int					count_lists(t_list_ps *nodes);
void				free_stack(t_list_ps **stack);
int					get_value(t_list_ps *node);
int					sort_two_or_three(t_list_ps **a);
void				push_back_to_a(t_list_ps **a, t_list_ps **b);
void				rotate_a_to_min(t_list_ps **a);
void				rotate_a_to_max(t_list_ps **b);
t_list_ps			*parse_args(int argc, char **argv);
void				error_exit(t_list_ps **stack);
long				safe_atoi(char *str, t_list_ps **stack);
int					is_duplicate(int val, t_list_ps *stack);
void				mark_lis_nodes(t_list_ps *a);
void				set_keep_flags(t_mark *m);
int					*find_lis_indexes(t_list_ps *a, int *lis_len);
int					*build_lis_indexes(int *prev, int lis_len, int max_end);
int					update_lis(int *arr, int *lengths, int *prev, int i);
void				copy_list_to_array(t_list_ps *a, int *arr);
void				initialize_arrays(int *lengths, int *prev, int size);
int					find_lis_dp(int *arr, int *lengths, int *prev, int size);
void				sort_five_or_less(t_list_ps **a, t_list_ps **b);
void				push_unmarked_nodes(t_list_ps **a, t_list_ps **b);
int					find_min_position(t_list_ps *a, int min);
int					exists_unmarked(t_list_ps *a);
int					calc_costs(int ra, int rb, int rra, int rrb);
int					select_pattern(t_move m, int cost);
t_cheap				update_best(t_best_ctx ctx, t_cheap best);
t_cheap				calculate(t_list_ps *a, t_list_ps *b);
void				exec_pat_1(t_list_ps **a, t_list_ps **b, t_cheap mv);
void				exec_pat_2(t_list_ps **a, t_list_ps **b,
						int rra_a, int rrb_b);
void				exec_pat_3(t_list_ps **a, t_list_ps **b,
						t_cheap mv, int rrb_b);
void				exec_pat_4(t_list_ps **a, t_list_ps **b,
						int rra_a, t_cheap mv);
void				execute_pattern(
						t_list_ps **a, t_list_ps **b, t_cheap mv, t_rot rot);
int					validate_digits(char *str, int i);
int					check_sign(char *str, long *i);
int					is_sorted(t_list_ps *a);
void				handle_error(char *line, t_list_ps **a, t_list_ps **b);
void				copy_list_to_array(t_list_ps *stack_a, int *arr);
void				initialize_arrays(int *lengths, int *prev, int size);

#endif
