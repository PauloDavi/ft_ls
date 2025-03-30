/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_directory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobli <cobli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 09:37:12 by cobli             #+#    #+#             */
/*   Updated: 2025/03/30 17:36:28 by cobli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>

#include "ft_ls.h"

static bool add_entry(const char *path, struct dirent *entry, t_list **list);

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

  order_files(list, flags);
  print_files(list, flags);
  ft_lstclear(&list, free_entry);
  return true;
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
