/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobli <cobli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 17:45:09 by cobli             #+#    #+#             */
/*   Updated: 2025/03/30 23:24:24 by cobli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/stat.h>

#include "ft_ls.h"

static bool create_default_dir(t_list **directories);
static bool add_entry(t_list **files, const struct stat *file_stat, t_list **directories, const char *arg);

bool parse_args(t_list **files, t_list **directories, int argc, char **argv) {
  *files = NULL;
  *directories = NULL;

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-' && argv[i][1] != '\0') {
      continue;
    }

    struct stat file_stat;
    if (lstat(argv[i], &file_stat) < 0) {
      ft_fprintf(STDERR_FILENO, "%s: cannot access '%s': No such file or directory\n", argv[0], argv[i]);
      continue;
    }

    if (!add_entry(files, &file_stat, directories, argv[i])) {
      return (false);
    }
  }

  if (*files == NULL && *directories == NULL) {
    create_default_dir(directories);
  }

  return (true);
}

static bool add_entry(t_list **files, const struct stat *file_stat, t_list **directories, const char *arg) {
  char *name = ft_strdup(arg);
  if (!name) {
    perror("malloc");
    ft_lstclear(files, free);
    ft_lstclear(directories, free);
    return (false);
  }
  t_list *new_content = ft_lstnew(name);
  if (!new_content) {
    perror("malloc");
    ft_lstclear(files, free);
    ft_lstclear(directories, free);
    return (false);
  }
  if (S_ISDIR(file_stat->st_mode)) {
    ft_lstadd_back(directories, new_content);
  } else {
    ft_lstadd_back(files, new_content);
  }

  return (true);
}

static bool create_default_dir(t_list **directories) {
  char *name = ft_strdup(".");
  if (!name) {
    perror("malloc");
    return (false);
  }
  t_list *new_content = ft_lstnew(name);
  if (!new_content) {
    perror("malloc");
    free(name);
    return (false);
  }
  ft_lstadd_back(directories, new_content);
  return (true);
}
