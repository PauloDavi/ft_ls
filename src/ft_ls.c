/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobli <cobli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 09:37:15 by cobli             #+#    #+#             */
/*   Updated: 2025/04/01 22:58:49 by cobli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int main(int argc, char **argv) {
  t_flags flags;

  if (!parse_flags(&flags, argc, argv)) {
    return (EXIT_FAILURE);
  }

  t_list *files = NULL;
  t_list *directories = NULL;
  if (!parse_args(&files, &directories, argc, argv, &flags)) {
    return (EXIT_FAILURE);
  }

  bool has_files = files != NULL;
  if (has_files) {
    display_list(files, &flags, true);
    ft_lstclear(&files, free_entry);
  }

  int exit_code = EXIT_SUCCESS;
  if (directories != NULL && !list_directories(directories, &flags, has_files)) {
    exit_code = EXIT_FAILURE;
  }

  ft_lstclear(&directories, free_entry);
  return (exit_code);
}
