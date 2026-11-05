/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmura <tmura@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 14:10:45 by tmura             #+#    #+#             */
/*   Updated: 2025/07/12 14:10:47 by tmura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_BONUS_H
# define PUSH_SWAP_BONUS_H

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

t_list_ps		*ft_lstlast_ps(t_list_ps *lst);
t_list_ps		*parse_args(int argc, char **argv);
t_list_ps		*new_node(int value);
char			*expand_buffer(char *buffer, int *capacity, int length);
int				read_line(char *buffer, int capacity);
int				get_next_line(char **line);
void			execute_instruction(char *line, t_list_ps **a, t_list_ps **b);
void			read_and_execute(t_list_ps **a, t_list_ps **b);
void			error_exit(t_list_ps **stack);
void			handle_error(char *line, t_list_ps **a, t_list_ps **b);
void			pa(t_list_ps **a, t_list_ps **b);
void			pb(t_list_ps **a, t_list_ps **b);
int				rotate_head_tail(t_list_ps **node);
void			ra(t_list_ps **a);
void			rb(t_list_ps **b);
void			rr(t_list_ps **a, t_list_ps **b);
int				rotate_tail_head(t_list_ps **node);
void			rra(t_list_ps **a);
void			rrb(t_list_ps **b);
void			rrr(t_list_ps **a, t_list_ps **b);
int				check_sign(char *str, long *i);
int				validate_digits(char *str, int i);
long			safe_atoi(char *str, t_list_ps **a);
int				swap_top_two_nodes(t_list_ps **node);
int				is_duplicate(int val, t_list_ps *stack);
void			free_stack(t_list_ps **stack);
int				is_sorted(t_list_ps *a);
int				count_lists(t_list_ps *nodes);
void			sa(t_list_ps **a);
void			sb(t_list_ps **b);
void			ss(t_list_ps **a, t_list_ps **b);
void			add_back(t_list_ps **head, t_list_ps *new);

#endif
