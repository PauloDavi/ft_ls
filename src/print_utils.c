/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobli <cobli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 17:04:59 by cobli             #+#    #+#             */
/*   Updated: 2025/04/06 15:18:52 by cobli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>

#include "ft_ls.h"

static void print_entry(t_entry *entry, const t_tabulation *tab, const t_flags *flags);
static void print_total_blocks(t_list *list);
void print_entries(t_list *list, const t_flags *flags);
static void print_files(t_list *list, const t_flags *flags, bool is_files);
static void print_name(char *name, mode_t mode, bool is_executable, bool no_colors);

void display_list(t_list **list, const t_flags *flags, bool is_files) {
  if (flags->no_sort) {
    ft_lst_reverse(list);
  } else {
    order_files(list, flags);
  }
  print_files(*list, flags, is_files);
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
      print_name(entry->name, entry->mode, entry->is_executable, flags->no_colors);
      ft_printf("\n");
    }

    list = list->next;
  }
}

static void print_entry(t_entry *entry, const t_tabulation *tab, const t_flags *flags) {
  ft_printf("%-*s %*ld ", tab->max_permission, entry->permissions, tab->max_nlink, entry->nlink);
  if (!flags->no_owner) {
    ft_printf("%-*s ", tab->max_owner, entry->owner);
  }

  ft_printf("%-*s ", tab->max_group, entry->group);

  if (entry->is_special) {
    ft_printf("%*d, %*d ", tab->max_major, entry->major, tab->max_minor, entry->minor);
  } else {
    ft_printf("%*ld ", tab->max_size, entry->size);
  }

  ft_printf("%s ", entry->s_time);

  print_name(entry->name, entry->mode, entry->is_executable, flags->no_colors);
  if (entry->link) {
    ft_printf(" -> ");
    print_name(entry->link->name, entry->link->mode, entry->link->is_executable, flags->no_colors);
  }
  ft_printf("\n");
}

static void print_name(char *name, mode_t mode, bool is_executable, bool no_colors) {
  if (no_colors) {
    ft_printf("%s", name);
    return;
  }

  if (S_ISDIR(mode)) {
    if ((mode & S_ISVTX) && (mode & S_IWOTH)) {
      ft_printf(BLACK_GREENBG "%s" RESET, name);
    } else if ((mode & S_IWOTH)) {
      ft_printf(BLUE_GREENBG "%s" RESET, name);
    } else if ((mode & S_ISVTX)) {
      ft_printf(WHITE_BLUEBG "%s" RESET, name);
    } else {
      ft_printf(BBLUE "%s" RESET, name);
    }
  } else if (S_ISLNK(mode)) {
    ft_printf(BCYAN "%s" RESET, name);
  } else if (S_ISSOCK(mode)) {
    ft_printf(BMAGENTA "%s" RESET, name);
  } else if (S_ISFIFO(mode)) {
    ft_printf(YELLOW_BLACKBG "%s" RESET, name);
  } else if (S_ISBLK(mode)) {
    ft_printf(YELLOW_BLACKBG_BOLD "%s" RESET, name);
  } else if (S_ISCHR(mode)) {
    ft_printf(YELLOW_BLACKBG_BOLD "%s" RESET, name);
  } else if (mode & S_ISUID) {
    ft_printf(WHITE_REDBG "%s" RESET, name);
  } else if (mode & S_ISGID) {
    ft_printf(BLACK_YELLOWBG "%s" RESET, name);
  } else if (is_executable) {
    ft_printf(BGREEN "%s" RESET, name);
  } else {
    ft_printf("%s", name);
  }
}
