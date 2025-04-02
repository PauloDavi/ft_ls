/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobli <cobli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 17:45:09 by cobli             #+#    #+#             */
/*   Updated: 2025/04/01 22:36:28 by cobli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/stat.h>

#include "ft_ls.h"

static bool parse_flag(const char *arg, t_flags *flags);

bool parse_flags(t_flags *flags, int argc, char **argv) {
  ft_memset(flags, 0, sizeof(t_flags));

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-' && argv[i][1] != '\0' && !parse_flag(argv[i], flags)) {
      ft_fprintf(STDERR_FILENO, "%s: invalid option -- '%s'\n", argv[0], argv[i]);
      return (false);
    }
  }

  return (true);
}

static bool parse_flag(const char *arg, t_flags *flags) {
  for (int i = 1; arg[i] != '\0'; i++) {
    if (arg[i] == 'l')
      flags->list = true;
    else if (arg[i] == 'a')
      flags->all = true;
    else if (arg[i] == 'r')
      flags->reverse = true;
    else if (arg[i] == 't')
      flags->time = true;
    else if (arg[i] == 'R')
      flags->recursive = true;
    else if (arg[i] == 'u')
      flags->access = true;
    else if (arg[i] == 'f')
      flags->no_sort = true;
    else if (arg[i] == 'g')
      flags->no_owner = true;
    else if (arg[i] == 'd')
      flags->files_only = true;
    else
      return (false);
  }

  return (true);
}
