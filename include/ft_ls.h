#ifndef FT_LS_H
#define FT_LS_H

#include <dirent.h>
#include <stdbool.h>
#include <sys/types.h>

#include "libft.h"

typedef struct s_flags {
  bool all;
  bool list;
  bool recursive;
  bool reverse;
  bool time;
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
} t_entry;

typedef struct s_tabulation {
  size_t max_nlink;
  size_t max_owner;
  size_t max_group;
  size_t max_size;
} t_tabulation;

bool list_directory(const char *path, const t_flags *flags);
t_entry *create_entry(const char *path, struct dirent *dirent);
void order_files(t_list *list, const t_flags *flags);
void free_entry(void *entry);
void print_files(t_list *list, const t_flags *flags);
t_tabulation find_max_tabulations(t_list *list);

#endif
