/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_directories.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdavi-al <pdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 09:37:12 by cobli             #+#    #+#             */
/*   Updated: 2025/06/22 13:26:16 by pdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>

#include "ft_ls.h"

/**
 * @brief List the contents of a single directory.
 * @param path Directory path
 * @param flags Flags struct
 * @param show_dir_name Whether to print the directory name
 * @param break_line_before Whether to print a newline before the directory
 * @return true on success, false on error
 */
static bool list_directory(const char *path, const t_flags *flags, bool show_dir_name, bool break_line_before);

/**
 * @brief Recursively call listing for subdirectories.
 * @param list List of entries
 * @param path Current directory path
 * @param flags Flags struct
 */
static void recursive_call(t_list *list, const char *path, const t_flags *flags);

/**
 * @brief List all directories in the list, printing names if needed.
 * @param directories List of directories
 * @param flags Flags struct
 * @param has_files_before Whether files were printed before
 * @return true on success, false on error
 */
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
  return true;
}

static bool list_directory(const char *path, const t_flags *flags, bool show_dir_name, bool break_line_before) {
  DIR *dir;
  struct dirent *entry;

  dir = opendir(path);
  if (dir == NULL) {
    ft_fprintf(STDERR_FILENO, "ls: cannot open directory '%s': Permission denied\n", path);
    return false;
  }

  if (show_dir_name) {
    if (break_line_before) ft_printf("\n");
    if (flags->comma) {
      ft_printf("\"%s\":\n", path);
    } else {
      ft_printf("%s:\n", path);
    }
  }

  t_list *list = NULL;
  while ((entry = readdir(dir)) != NULL) {
    // Skip hidden files if not showing all
    if (entry->d_name[0] == '.' && !flags->all) {
      continue;
    }
    if (!add_entry(path, entry->d_name, &list, flags)) {
      closedir(dir);
      return false;
    }
  }
  closedir(dir);

  display_list(&list, flags, false);

  // Recursive call for subdirectories if needed
  if (flags->recursive) {
    recursive_call(list, path, flags);
  }

  ft_lstclear(&list, free_entry);
  return true;
}

static void recursive_call(t_list *list, const char *path, const t_flags *flags) {
  while (list != NULL) {
    t_entry *entry = (t_entry *)list->content;
    // Only recurse into subdirectories, skip . and ..
    if (entry->permissions[0] == 'd' && ft_strcmp(entry->name, ".") != 0 && ft_strcmp(entry->name, "..") != 0) {
      char new_path[PATH_MAX];
      concat_paths(new_path, path, entry->name);
      list_directory(new_path, flags, true, true);
    }
    list = list->next;
  }
}
