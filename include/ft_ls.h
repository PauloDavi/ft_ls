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
  -d --directory      list directories themselves, not their contents\n\
  -N --literal        print entry names without quoting\n\
  -Q --quote-name     enclose entry names in double quotes\n\
  -m                  fill width with a comma separated list of entries\n\
  --color             colorize the output\n"

typedef struct s_flags {
  bool all;         // -a -> Show hidden files
  bool almost_all;  // -A -> Show hidden files except . and ..
  bool list;        // -l -> Detailed display
  bool recursive;   // -R -> Recursive listing
  bool reverse;     // -r -> Reverse order
  bool time;        // -t -> Sort by modification time
  bool access;      // -u -> Sort by access time
  bool no_sort;     // -f -> Disable sorting
  bool no_owner;    // -g -> Similar to -l, but without owner name
  bool files_only;  // -d -> List directories as regular files
  bool quote_name;  // -Q -> Enclose entry names in double quotes
  bool comma;       // -m -> Comma-separated list
  bool color;       // --color -> Colorize the output
} t_flags;

typedef struct s_link {
  char *name;
  mode_t mode;
  bool exist;
  bool is_executable;
} t_link;

typedef struct s_entry {
  char *name;
  char permissions[12];
  char *owner;
  char *group;
  blkcnt_t blocks;
  off_t size;
  nlink_t nlink;
  char *s_time;
  time_t time_sec;
  long time_nsec;
  t_link *link;
  mode_t mode;
  bool is_executable;
  bool is_special;
  int major;
  int minor;
} t_entry;

typedef struct s_tabulation {
  size_t max_permission;
  size_t max_nlink;
  size_t max_owner;
  size_t max_group;
  size_t max_size;
  size_t max_major;
  size_t max_minor;
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
