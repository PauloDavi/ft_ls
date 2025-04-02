/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobli <cobli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 17:04:59 by cobli             #+#    #+#             */
/*   Updated: 2025/04/02 00:17:47 by cobli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void print_entry(t_entry *entry, const t_tabulation *tab, const t_flags *flags);
static void print_total_blocks(t_list *list);
void print_entries(t_list *list, const t_flags *flags);
static void print_files(t_list *list, const t_flags *flags, bool is_files);
static void print_name(char *name, char permission, bool is_executable, bool no_colors);

void display_list(t_list *list, const t_flags *flags, bool is_files) {
  if (flags->no_sort) {
    ft_lst_revert(list);
  } else {
    order_files(list, flags);
  }
  print_files(list, flags, is_files);
}

static void print_files(t_list *list, const t_flags *flags, bool is_files) {
  if (flags->list) {
    if (!is_files) print_total_blocks(list);
  }
  print_entries(list, flags);
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

void print_entries(t_list *list, const t_flags *flags) {
  t_tabulation tab = find_max_tabulations(list);
  while (list != NULL) {
    t_entry *entry = list->content;
    if (flags->list) {
      print_entry(entry, &tab, flags);
    } else {
      print_name(entry->name, entry->permissions[0], entry->is_executable, flags->no_colors);
      ft_printf("\n");
    }

    list = list->next;
  }
}

static void print_entry(t_entry *entry, const t_tabulation *tab, const t_flags *flags) {
  ft_printf("%s %*ld ", entry->permissions, tab->max_nlink, entry->nlink);
  if (!flags->no_owner) {
    ft_printf("%*s ", tab->max_owner, entry->owner);
  }
  ft_printf("%*s %*ld %s ", tab->max_group, entry->group, tab->max_size, entry->size, entry->s_time);

  print_name(entry->name, entry->permissions[0], entry->is_executable, flags->no_colors);
  if (entry->link) {
    ft_printf(" -> %s", entry->link);
  }
  ft_printf("\n");
}

static void print_name(char *name, char permission, bool is_executable, bool no_colors) {
  if (no_colors) {
    ft_printf("%s", name);
    return;
  }

  if (permission == 'd') {
    ft_printf(BLUE "%s" RESET, name);
  } else if (permission == 'l') {
    ft_printf(CYAN "%s" RESET, name);
  } else if (is_executable) {
    ft_printf(GREEN "%s" RESET, name);
  } else {
    ft_printf("%s", name);
  }
}
