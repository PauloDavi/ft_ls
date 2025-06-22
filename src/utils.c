/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdavi-al <pdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 21:02:47 by cobli             #+#    #+#             */
/*   Updated: 2025/06/22 13:24:45 by pdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <linux/limits.h>

#include "ft_ls.h"

/**
 * @brief Concatenate a directory path and filename into dest, ensuring not to exceed PATH_MAX.
 * @param dest Destination buffer
 * @param path Directory path
 * @param filename File name
 */
void concat_paths(char *dest, const char *path, const char *filename) {
  size_t path_len = ft_strlen(path);
  size_t filename_len = ft_strlen(filename);

  if (path_len + filename_len + 2 > PATH_MAX) {
    // Path too long, do not concatenate
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
