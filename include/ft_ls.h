#ifndef FT_LS_H
#define FT_LS_H

#include <dirent.h>
#include <stdbool.h>
#include <sys/types.h>

#include "libft.h"

#define BLUE "\033[1;34m"
#define GREEN "\033[1;32m"
#define CYAN "\033[1;36m"
#define RESET "\033[0m"

typedef struct s_flags {
  bool all;         // -a -> Show hidden files
  bool list;        // -l -> Detailed display
  bool recursive;   // -R -> Recursive listing
  bool reverse;     // -r -> Reverse order
  bool time;        // -t -> Sort by modification time
  bool access;      // -u -> Sort by access time
  bool no_sort;     // -f -> Disable sorting
  bool no_owner;    // -g -> Similar to -l, but without owner name
  bool files_only;  // -d -> List directories as regular files
  bool no_colors;   // when -f -> Disable colors
} t_flags;

typedef struct s_entry {
  char *name;
  char permissions[11];
  char *owner;
  char *group;
  blkcnt_t blocks;
  off_t size;
  nlink_t nlink;
  char *s_time;
  time_t time_sec;
  long time_nsec;
  char *link;
  bool is_executable;
} t_entry;

typedef struct s_tabulation {
  size_t max_nlink;
  size_t max_owner;
  size_t max_group;
  size_t max_size;
} t_tabulation;

bool list_directories(t_list *list, const t_flags *flags, bool has_files_before);
bool add_entry(const char *path, const char *filename, t_list **list, const t_flags *flags);
void order_files(t_list *list, const t_flags *flags);
t_entry *create_entry(const char *path, const char *filename, const t_flags *flags);
bool parse_flags(t_flags *flags, int argc, char **argv);
bool parse_args(t_list **files, t_list **directories, int argc, char **argv, const t_flags *flags);
void free_entry(void *entry);
void concat_paths(char *dest, const char *path, const char *filename);
void display_list(t_list *list, const t_flags *flags, bool is_files);
t_tabulation find_max_tabulations(t_list *list);

#endif
