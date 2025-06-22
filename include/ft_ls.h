/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdavi-al <pdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:02:36 by pdavi-al          #+#    #+#             */
/*   Updated: 2025/06/22 14:02:36 by pdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
#define FT_LS_H

#include <dirent.h>
#include <stdbool.h>
#include <sys/types.h>

#include "color.h"
#include "libft.h"

#define HELP \
  "Usage: %s [OPTION]... [FILE]...\n\
  -a, --all           do not ignore entries starting with .\n\
  -A, --almost-all    do not list implied . and ..\n\
  -l                  use a long listing format\n\
  -R, --recursive     list subdirectories recursively\n\
  -r, --reverse       reverse order while sorting\n\
  -t                  sort by time modified (most recent first)\n\
  -u                  access time instead of modification time\n\
  -f                  do not sort, enable -a and disable -l\n\
  -g                  like -l, but do not list owner\n\
  -G, --no-group      \n\
  -d --directory      list directories themselves, not their contents\n\
  -N --literal        print entry names without quoting\n\
  -Q --quote-name     enclose entry names in double quotes\n\
  -m                  fill width with a comma separated list of entries\n\
  --color             colorize the output\n"

/**
 * @struct s_flags
 * @brief Stores all command-line flags and options for ft_ls.
 */
typedef struct s_flags {
  bool all;        /**< -a: Show hidden files */
  bool almost_all; /**< -A: Show hidden files except . and .. */
  bool list;       /**< -l: Detailed display */
  bool recursive;  /**< -R: Recursive listing */
  bool reverse;    /**< -r: Reverse order */
  bool time;       /**< -t: Sort by modification time */
  bool access;     /**< -u: Sort by access time */
  bool no_sort;    /**< -f: Disable sorting */
  bool no_owner;   /**< -g: Like -l, but without owner name */
  bool no_group;   /**< -G: Like -l, but without group name */
  bool files_only; /**< -d: List directories as regular files */
  bool quote_name; /**< -Q: Enclose entry names in double quotes */
  bool comma;      /**< -m: Comma-separated list */
  bool color;      /**< --color: Colorize the output */
} t_flags;

/**
 * @struct s_link
 * @brief Stores information about a symbolic link.
 */
typedef struct s_link {
  char *name;         /**< Link target name */
  mode_t mode;        /**< Link target mode */
  bool exist;         /**< Whether the link target exists */
  bool is_executable; /**< Whether the link target is executable */
} t_link;

/**
 * @struct s_entry
 * @brief Represents a file or directory entry with all metadata needed for display.
 */
typedef struct s_entry {
  char *name;           /**< File or directory name */
  char permissions[12]; /**< Permissions string (e.g. "-rwxr-xr-x") */
  char *owner;          /**< Owner name */
  char *group;          /**< Group name */
  blkcnt_t blocks;      /**< Number of blocks */
  off_t size;           /**< File size in bytes */
  nlink_t nlink;        /**< Number of hard links */
  char *s_time;         /**< Formatted time string */
  time_t time_sec;      /**< Time (seconds) for sorting */
  long time_nsec;       /**< Time (nanoseconds) for sorting */
  t_link *link;         /**< Symbolic link info (if applicable) */
  mode_t mode;          /**< File mode (type and permissions) */
  bool is_executable;   /**< Whether the file is executable */
  bool is_special;      /**< Whether the file is a special device */
  int major;            /**< Major device number (if special) */
  int minor;            /**< Minor device number (if special) */
} t_entry;

/**
 * @struct s_tabulation
 * @brief Stores maximum widths for each column for pretty-printing tables.
 */
typedef struct s_tabulation {
  size_t max_permission; /**< Max width for permissions column */
  size_t max_nlink;      /**< Max width for nlink column */
  size_t max_owner;      /**< Max width for owner column */
  size_t max_group;      /**< Max width for group column */
  size_t max_size;       /**< Max width for size column */
  size_t max_major;      /**< Max width for major device column */
  size_t max_minor;      /**< Max width for minor device column */
} t_tabulation;

bool list_directories(t_list *list, const t_flags *flags, bool has_files_before);
bool add_entry(const char *path, const char *filename, t_list **list, const t_flags *flags);
void order_files(t_list **list, const t_flags *flags);
t_entry *create_entry(const char *path, const char *filename, const t_flags *flags);
bool parse_flags(t_flags *flags, int argc, char **argv);
bool parse_args(t_list **files, t_list **directories, int argc, char **argv, const t_flags *flags);
void free_entry(void *entry);
void concat_paths(char *dest, const char *path, const char *filename);
void display_list(t_list **list, const t_flags *flags, bool is_files);
t_tabulation find_max_tabulations(t_list *list);
void print_columns(t_list *list, const t_flags *flags);
void print_name(char *filename, mode_t mode, bool is_executable, bool no_colors, bool has_quote, size_t len);
void print_comma(t_list *list, const t_flags *flags);

#endif
