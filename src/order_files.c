/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdavi-al <pdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 17:08:50 by cobli             #+#    #+#             */
/*   Updated: 2025/06/22 13:25:18 by pdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/**
 * @brief Compare two entries alphabetically by name.
 * @param a Pointer to first entry
 * @param b Pointer to second entry
 * @return <0 if a < b, 0 if equal, >0 if a > b
 */
static int alphabetical_order(void *a, void *b);

/**
 * @brief Compare two entries by modification time.
 * @param a Pointer to first entry
 * @param b Pointer to second entry
 * @return <0 if a < b, 0 if equal, >0 if a > b
 */
static int time_order(void *a, void *b);

/**
 * @brief Sort the file list according to flags (by time or alphabetically, and reverse if needed).
 * @param list Pointer to the list to sort
 * @param flags Flags struct
 */
void order_files(t_list **list, const t_flags *flags) {
  if (flags->time) {
    ft_lst_sort(list, time_order);
  } else {
    ft_lst_sort(list, alphabetical_order);
  }
  if (flags->reverse) {
    ft_lst_reverse(list);
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
