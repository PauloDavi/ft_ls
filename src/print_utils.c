/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobli <cobli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 17:04:59 by cobli             #+#    #+#             */
/*   Updated: 2025/04/01 20:38:58 by cobli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void print_entry_name(void *content);
static void print_entry(t_entry *entry, t_tabulation tab);
static void print_total_blocks(t_list *list);
void print_entries(t_list *lst, t_tabulation tab);
static void print_files(t_list *list, const t_flags *flags, bool is_files);

void display_list(t_list *list, const t_flags *flags, bool is_files) {
  order_files(list, flags);
  print_files(list, flags, is_files);
}

static void print_files(t_list *list, const t_flags *flags, bool is_files) {
  if (flags->list) {
    if (!is_files) print_total_blocks(list);
    t_tabulation tab = find_max_tabulations(list);
    print_entries(list, tab);
  } else {
    ft_lstiter(list, print_entry_name);
  }
}

static void print_total_blocks(t_list *list) {
  long total = 0;
  t_list *current = list;

  while (current) {
    t_entry *entry = (t_entry *)current->content;
    total += entry->blocks;
    current = current->next;
  }
  ft_printf("total %ld\n", total / 2);
}

static void print_entry_name(void *content) {
  t_entry *entry = (t_entry *)content;
  ft_printf("%s\n", entry->name);
}

void print_entries(t_list *lst, t_tabulation tab) {
  while (lst != NULL) {
    print_entry(lst->content, tab);
    lst = lst->next;
  }
}

static void print_entry(t_entry *entry, t_tabulation tab) {
  ft_printf("%s %*ld %*s %*s %*ld %s %s",
            entry->permissions,
            tab.max_nlink,
            entry->nlink,
            tab.max_owner,
            entry->owner,
            tab.max_group,
            entry->group,
            tab.max_size,
            entry->size,
            entry->s_time,
            entry->name);
  if (entry->link) {
    ft_printf(" -> %s", entry->link);
  }
  ft_printf("\n");
}
