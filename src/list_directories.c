/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_directories.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobli <cobli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 09:37:12 by cobli             #+#    #+#             */
/*   Updated: 2025/03/31 00:11:35 by cobli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>

#include "ft_ls.h"

static bool list_directory(const char *path, const t_flags *flags);

bool list_directories(t_list *list, const t_flags *flags, bool has_files_before) {
  bool show_dir_name = has_files_before || ft_lstsize(list) > 1;
  t_list *current = list;
  while (current != NULL) {
    if (show_dir_name) {
      ft_printf("\n%s:\n", current->content);
    }
    if (!list_directory(current->content, flags)) {
      return false;
    }
    current = current->next;
  }
  return true;
}

static bool list_directory(const char *path, const t_flags *flags) {
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
    if (!add_entry(path, entry->d_name, &list)) {
      closedir(dir);
      return false;
    }
  }
  closedir(dir);

  display_list(list, flags, false);
  return true;
}
