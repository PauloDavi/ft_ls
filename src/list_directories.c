/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_directories.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobli <cobli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 09:37:12 by cobli             #+#    #+#             */
/*   Updated: 2025/04/01 22:59:35 by cobli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>

#include "ft_ls.h"

static bool list_directory(const char *path, const t_flags *flags, bool show_dir_name, bool break_line_before);
static void recursive_call(t_list *list, const char *path, const t_flags *flags);

bool list_directories(t_list *directories, const t_flags *flags, bool has_files_before) {
  bool show_dir_name = has_files_before || ft_lstsize(directories) > 1 || flags->recursive;

  t_list *current = directories;
  while (current != NULL) {
    list_directory(
        ((t_entry *)(current->content))->name,
        flags,
        show_dir_name,
        has_files_before || current != directories);
    current = current->next;
  }
  return (true);
}

static bool list_directory(const char *path, const t_flags *flags, bool show_dir_name, bool break_line_before) {
  DIR *dir;
  struct dirent *entry;

  dir = opendir(path);
  if (dir == NULL) {
    perror("opendir");
    return (false);
  }

  if (show_dir_name) {
    if (break_line_before) ft_printf("\n");
    ft_printf("%s:\n", path);
  }

  t_list *list = NULL;
  while ((entry = readdir(dir)) != NULL) {
    if (entry->d_name[0] == '.' && !flags->all) {
      continue;
    }
    if (!add_entry(path, entry->d_name, &list, flags)) {
      closedir(dir);
      return (false);
    }
  }
  closedir(dir);

  display_list(list, flags, false);

  if (flags->recursive) {
    recursive_call(list, path, flags);
  }

  ft_lstclear(&list, free_entry);
  return (true);
}

static void recursive_call(t_list *list, const char *path, const t_flags *flags) {
  while (list != NULL) {
    t_entry *entry = (t_entry *)list->content;
    if (entry->permissions[0] == 'd' && ft_strcmp(entry->name, ".") != 0 && ft_strcmp(entry->name, "..") != 0) {
      char new_path[PATH_MAX];
      concat_paths(new_path, path, entry->name);
      list_directory(new_path, flags, true, true);
    }
    list = list->next;
  }
}
