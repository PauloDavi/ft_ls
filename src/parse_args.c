/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdavi-al <pdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 17:45:09 by cobli             #+#    #+#             */
/*   Updated: 2025/06/22 13:26:47 by pdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/stat.h>

#include "ft_ls.h"

/**
 * @brief Add a file or directory entry to the appropriate list.
 * @param files Pointer to the file list
 * @param directories Pointer to the directory list
 * @param entry The entry to add
 * @param flags The flags struct
 * @return true on success, false on allocation error
 */
static bool add_file(t_list **files, t_list **directories, t_entry *entry, const t_flags *flags);

/**
 * @brief Create the default directory entry (".") if no files or directories are given.
 * @param files Pointer to the file list
 * @param directories Pointer to the directory list
 * @param flags The flags struct
 * @return true on success, false on allocation error
 */
static bool create_default_dir(t_list **files, t_list **directories, const t_flags *flags);

/**
 * @brief Parse command-line arguments into file and directory lists.
 *
 * This function separates arguments into files and directories, initializing the lists.
 *
 * @param files Pointer to the file list
 * @param directories Pointer to the directory list
 * @param argc Argument count
 * @param argv Argument vector
 * @param flags The flags struct
 * @return true on success, false on allocation error
 */
bool parse_args(t_list **files, t_list **directories, int argc, char **argv, const t_flags *flags) {
  *files = NULL;
  *directories = NULL;

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-' && argv[i][1] != '\0') {
      continue; /**< Skip flags. */
    }

    t_entry *entry = create_entry(NULL, argv[i], flags);
    if (entry == NULL) {
      ft_fprintf(STDERR_FILENO, "%s: cannot access '%s': No such file or directory\n", argv[0], argv[i]);
      continue;
    }

    if (!add_file(files, directories, entry, flags)) {
      ft_lstclear(files, free_entry);
      ft_lstclear(directories, free_entry);
      free(entry);
      return false;
    }
  }

  if (*files == NULL && *directories == NULL) {
    return create_default_dir(files, directories, flags);
  }

  return true;
}

static bool add_file(t_list **files, t_list **directories, t_entry *entry, const t_flags *flags) {
  t_list *new_content = ft_lstnew(entry);
  if (!new_content) {
    perror("malloc");
    return false;
  }

  if (!flags->files_only && entry->permissions[0] == 'd') {
    ft_lstadd_front(directories, new_content);
  } else {
    ft_lstadd_front(files, new_content);
  }

  return true;
}

static bool create_default_dir(t_list **files, t_list **directories, const t_flags *flags) {
  t_entry *entry = create_entry(NULL, ".", flags);
  if (!add_file(files, directories, entry, flags)) {
    free(entry);
    return false;
  }

  return true;
}
