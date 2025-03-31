/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobli <cobli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 09:37:15 by cobli             #+#    #+#             */
/*   Updated: 2025/03/31 00:04:41 by cobli            ###   ########.fr       */
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
  if (!parse_args(&files, &directories, argc, argv)) {
    return (EXIT_FAILURE);
  }

  if (files != NULL && !list_files(files, &flags)) {
    ft_lstclear(&files, free);
    ft_lstclear(&directories, free);
    return (EXIT_FAILURE);
  }
  if (directories != NULL && !list_directories(directories, &flags, files != NULL)) {
    ft_lstclear(&files, free);
    ft_lstclear(&directories, free);
    return (EXIT_FAILURE);
  }

  ft_lstclear(&files, free);
  ft_lstclear(&directories, free);
  return (EXIT_SUCCESS);
}
