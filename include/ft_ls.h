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

bool list_directory(const char *path, const t_flags *flags);
t_entry *create_entry(const char *path, struct dirent *dirent);
void free_entry(void *entry);

#endif
