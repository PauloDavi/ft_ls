/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobli <cobli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 09:37:15 by cobli             #+#    #+#             */
/*   Updated: 2025/03/30 17:02:20 by cobli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int main(void) {
  t_flags flags;

  flags.all = true;
  flags.list = true;
  flags.reverse = true;
  flags.time = true;
  flags.recursive = false;

  if (!list_directory(".", &flags)) {
    return (EXIT_FAILURE);
  }

  return (EXIT_SUCCESS);
}
