/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdavi-al <pdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 17:45:09 by cobli             #+#    #+#             */
/*   Updated: 2025/06/22 13:34:24 by pdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/stat.h>

#include "ft_ls.h"

/**
 * @brief Parse a short flag argument (e.g. -lart) and set the corresponding fields in t_flags.
 * @param exec_name Name of the executable (for error messages)
 * @param arg Argument string (e.g. "-lart")
 * @param flags Pointer to the t_flags struct to update
 * @return true if all flags are valid, false otherwise
 */
static bool parse_flag(const char *exec_name, const char *arg, t_flags *flags);

/**
 * @brief Parse a long option argument (e.g. --all) and set the corresponding fields in t_flags.
 * @param exec_name Name of the executable (for error messages)
 * @param arg Argument string (e.g. "--all")
 * @param flags Pointer to the t_flags struct to update
 * @return true if the option is valid, false otherwise
 */
static bool parse_option(const char *exec_name, const char *arg, t_flags *flags);

/**
 * @brief Parse all command-line flags and options, initializing the t_flags struct.
 *
 * This function iterates over argv, processing both short flags (e.g. -lart)
 * and long options (e.g. --all), and sets the corresponding fields in t_flags.
 *
 * @param flags Pointer to the t_flags struct to initialize
 * @param argc Argument count
 * @param argv Argument vector
 * @return true if all flags/options are valid, false otherwise
 */
bool parse_flags(t_flags *flags, int argc, char **argv) {
  ft_memset(flags, 0, sizeof(t_flags));
  flags->color = true; /**< Color is enabled by default. */

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      if (argv[i][1] == '-' && argv[i][2] != '\0') {
        if (!parse_option(argv[0], argv[i], flags)) {
          return false;
        }
      } else if (argv[i][1] != '\0') {
        if (!parse_flag(argv[0], argv[i], flags)) {
          return false;
        }
      }
    }
  }
  return true;
}

static bool parse_option(const char *exec_name, const char *arg, t_flags *flags) {
  // Each else if handles a supported long option
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
    ft_printf(HELP, exec_name);
    return false;
  } else {
    // Unrecognized option
    ft_fprintf(STDERR_FILENO, "%s: unrecognized option '%s'\n", exec_name, arg);
    ft_fprintf(STDERR_FILENO, "Try '%s --help' for more information.\n", exec_name);
    return false;
  }
  return true;
}

static bool parse_flag(const char *exec_name, const char *arg, t_flags *flags) {
  for (int i = 1; arg[i] != '\0'; i++) {
    switch (arg[i]) {
      case 'l':
        flags->list = true;
        break;
      case 'a':
        flags->all = true;
        flags->almost_all = false;
        break;
      case 'A':
        flags->almost_all = true;
        flags->all = false;
        break;
      case 'r':
        flags->reverse = true;
        break;
      case 't':
        flags->time = true;
        break;
      case 'R':
        flags->recursive = true;
        break;
      case 'u':
        flags->access = true;
        break;
      case 'f':
        /**
         * -f disables sorting, enables -a, disables color, disables -l,
         * disables owner/group/time/reverse.
         */
        flags->no_sort = true;
        flags->all = true;
        flags->color = false;
        flags->list = false;
        flags->no_owner = false;
        flags->time = false;
        flags->reverse = false;
        break;
      case 'g':
        flags->no_owner = true;
        flags->list = true;
        break;
      case 'G':
        flags->no_group = true;
        break;
      case 'd':
        flags->files_only = true;
        break;
      case 'Q':
        flags->quote_name = true;
        break;
      case 'N':
        flags->quote_name = false;
        break;
      case 'm':
        flags->comma = true;
        flags->list = false;
        break;
      case 'h':
      case 'H':
        break;  // Ignore -h and -H as they are not used in this implementation
      default:
        // Invalid flag
        ft_fprintf(STDERR_FILENO, "%s: invalid option -- '%c'\n", exec_name, arg[i]);
        ft_fprintf(STDERR_FILENO, "Try '%s --help' for more information.\n", exec_name);
        return false;
    }
  }
  return true;
}
