/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobli <cobli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 17:45:09 by cobli             #+#    #+#             */
/*   Updated: 2025/04/08 22:20:14 by cobli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/stat.h>

#include "ft_ls.h"

static bool parse_flag(const char *exec_name, const char *arg, t_flags *flags);
static bool parse_option(const char *exec_name, const char *arg, t_flags *flags);

bool parse_flags(t_flags *flags, int argc, char **argv) {
  ft_memset(flags, 0, sizeof(t_flags));
  flags->color = true;

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      if (argv[i][1] == '-' && argv[i][2] != '\0') {
        if (!parse_option(argv[0], argv[i], flags)) {
          return (false);
        }
      } else if (argv[i][1] != '\0') {
        if (!parse_flag(argv[0], argv[i], flags)) {
          return (false);
        }
      }
    }
  }

  return (true);
}

static bool parse_option(const char *exec_name, const char *arg, t_flags *flags) {
  if (ft_strcmp(arg, "--color") == 0) {
    flags->color = true;
  } else if (ft_strcmp(arg, "--reverse") == 0) {
    flags->reverse = true;
  } else if (ft_strcmp(arg, "--recursive") == 0) {
    flags->recursive = true;
  } else if (ft_strcmp(arg, "--literal") == 0) {
    flags->quote_name = false;
  } else if (ft_strcmp(arg, "--directory") == 0) {
    flags->files_only = true;
  } else if (ft_strcmp(arg, "--quote-name") == 0) {
    flags->quote_name = true;
  } else if (ft_strcmp(arg, "--almost-all") == 0) {
    flags->almost_all = true;
    flags->all = false;
  } else if (ft_strcmp(arg, "--all") == 0) {
    flags->all = true;
    flags->almost_all = false;
  } else if (ft_strcmp(arg, "--help") == 0) {
    ft_fprintf(STDOUT_FILENO, HELP, exec_name);
    return (false);
  } else {
    ft_fprintf(STDERR_FILENO, "%s: unrecognized option '%s'\n", exec_name, arg);
    ft_fprintf(STDERR_FILENO, "Try '%s --help' for more information.\n", exec_name);
    return (false);
  }

  return (true);
}

static bool parse_flag(const char *exec_name, const char *arg, t_flags *flags) {
  for (int i = 1; arg[i] != '\0'; i++) {
    if (arg[i] == 'l') {
      flags->list = true;
    } else if (arg[i] == 'a') {
      flags->all = true;
      flags->almost_all = false;
    } else if (arg[i] == 'A') {
      flags->almost_all = true;
      flags->all = false;
    } else if (arg[i] == 'r') {
      flags->reverse = true;
    } else if (arg[i] == 't') {
      flags->time = true;
    } else if (arg[i] == 'R') {
      flags->recursive = true;
    } else if (arg[i] == 'u') {
      flags->access = true;
    } else if (arg[i] == 'f') {
      flags->no_sort = true;
      flags->all = true;
      flags->color = false;
      flags->list = false;
      flags->no_owner = false;
      flags->time = false;
      flags->reverse = false;
    } else if (arg[i] == 'g') {
      flags->no_owner = true;
      flags->list = true;
    } else if (arg[i] == 'd') {
      flags->files_only = true;
    } else if (arg[i] == 'Q') {
      flags->quote_name = true;
    } else if (arg[i] == 'N') {
      flags->quote_name = false;
    } else if (arg[i] == 'm') {
      flags->comma = true;
      flags->list = false;
    } else {
      ft_fprintf(STDERR_FILENO, "%s: invalid option -- '%c'\n", exec_name, arg[i]);
      ft_fprintf(STDERR_FILENO, "Try '%s --help' for more information.\n", exec_name);
      return (false);
    }
  }

  return (true);
}
