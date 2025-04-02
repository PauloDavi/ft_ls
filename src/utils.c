/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobli <cobli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 21:02:47 by cobli             #+#    #+#             */
/*   Updated: 2025/04/01 21:03:18 by cobli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <linux/limits.h>

#include "ft_ls.h"

void concat_paths(char *dest, const char *path, const char *filename) {
  size_t path_len = ft_strlen(path);
  size_t filename_len = ft_strlen(filename);

  if (path_len + filename_len + 2 > PATH_MAX) {
    return;
  }

  ft_memcpy(dest, path, path_len);
  if (path[path_len - 1] != '/') {
    dest[path_len] = '/';
    path_len++;
  }
  ft_memcpy(dest + path_len, filename, filename_len);
  dest[path_len + filename_len] = '\0';
}
