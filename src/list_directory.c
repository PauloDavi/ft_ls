/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_directory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobli <cobli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 09:37:12 by cobli             #+#    #+#             */
/*   Updated: 2025/03/30 09:50:30 by cobli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>

#include "ft_ls.h"

void list_directory(char *path, t_flags flags) {
  DIR *dir;
  struct dirent *entry;

  dir = opendir(path);
  if (dir == NULL) {
    perror("opendir");
    return;
  }

  while ((entry = readdir(dir)) != NULL) {
    if (flags.all || entry->d_name[0] != '.') {
      ft_printf("%s\n", entry->d_name);
    }
  }

  closedir(dir);
}
