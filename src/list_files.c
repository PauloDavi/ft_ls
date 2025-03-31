/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobli <cobli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 23:43:37 by cobli             #+#    #+#             */
/*   Updated: 2025/03/30 23:46:47 by cobli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

bool list_files(t_list *files, const t_flags *flags) {
  t_list *list = NULL;
  t_list *current = files;
  while (current != NULL) {
    if (!add_entry(NULL, current->content, &list)) {
      return false;
    }
    current = current->next;
  }

  display_list(list, flags, true);
  return true;
}
