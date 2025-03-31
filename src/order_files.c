/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobli <cobli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 17:08:50 by cobli             #+#    #+#             */
/*   Updated: 2025/03/30 23:25:48 by cobli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int alphabetical_order(void *a, void *b);
static int time_order(void *a, void *b);

void order_files(t_list *list, const t_flags *flags) {
  if (flags->time) {
    ft_lst_sort(list, time_order);
  } else {
    ft_lst_sort(list, alphabetical_order);
  }

  if (flags->reverse) {
    ft_lst_revert(list);
  }
}

static int alphabetical_order(void *a, void *b) {
  t_entry *entry_a = (t_entry *)a;
  t_entry *entry_b = (t_entry *)b;

  return ft_strcmp(entry_a->name, entry_b->name);
}

static int time_order(void *a, void *b) {
  t_entry *entry_a = (t_entry *)a;
  t_entry *entry_b = (t_entry *)b;

  if (entry_a->time_sec != entry_b->time_sec) {
    return (entry_a->time_sec < entry_b->time_sec);
  }
  return (entry_a->time_nsec < entry_b->time_nsec);
}
