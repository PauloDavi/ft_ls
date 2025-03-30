/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_directory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobli <cobli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 09:37:12 by cobli             #+#    #+#             */
/*   Updated: 2025/03/30 16:21:25 by cobli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>

#include "ft_ls.h"

static int default_order(void *a, void *b);
static int time_order(void *a, void *b);
static bool add_entry(const char *path, struct dirent *entry, t_list **list);
static void print_entry_name(void *content);
static void print_entry(void *content);
static void print_total_blocks(t_list *list);
static void print_files(t_list *list, const t_flags *flags);

bool list_directory(const char *path, const t_flags *flags) {
  DIR *dir;
  struct dirent *entry;

  dir = opendir(path);
  if (dir == NULL) {
    perror("opendir");
    return false;
  }

  t_list *list = NULL;
  while ((entry = readdir(dir)) != NULL) {
    if (entry->d_name[0] == '.' && !flags->all) {
      continue;
    }
    if (!add_entry(path, entry, &list)) {
      closedir(dir);
      return false;
    }
  }
  closedir(dir);

  print_files(list, flags);
  ft_lstclear(&list, free_entry);
  return true;
}

static void print_files(t_list *list, const t_flags *flags) {
  if (flags->time) {
    ft_lst_sort(list, time_order);
  } else {
    ft_lst_sort(list, default_order);
  }

  if (flags->reverse) {
    ft_lst_revert(list);
  }

  if (flags->list) {
    print_total_blocks(list);
    ft_lstiter(list, print_entry);
  } else {
    ft_lstiter(list, print_entry_name);
  }
}

static int default_order(void *a, void *b) {
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

static bool add_entry(const char *path, struct dirent *dirent, t_list **list) {
  t_entry *entry = create_entry(path, dirent);
  if (entry == NULL) {
    perror("malloc");
    ft_lstclear(list, free_entry);
    return false;
  }

  t_list *new_node = ft_lstnew(entry);
  if (new_node == NULL) {
    perror("malloc");
    free_entry(entry);
    ft_lstclear(list, free_entry);
    return false;
  }

  if (list == NULL) {
    *list = new_node;
  } else {
    ft_lstadd_back(list, new_node);
  }

  return true;
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

static void print_entry(void *content) {
  t_entry *entry = (t_entry *)content;
  ft_printf("%s %*ld %s %s %6ld %s %s",
            entry->permissions,
            2,
            entry->nlink,
            entry->owner,
            entry->group,
            entry->size,
            entry->s_time,
            entry->name);
  if (entry->link) {
    ft_printf(" -> %s", entry->link);
  }
  ft_printf("\n");
}
