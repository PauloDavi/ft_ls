#ifndef FT_LS_H
#define FT_LS_H

#include <stdbool.h>

#include "libft.h"

typedef struct s_flags {
  bool all;
  bool list;
  bool recursive;
  bool reverse;
  bool time;
} t_flags;

void list_directory(char *path, t_flags flags);

#endif
