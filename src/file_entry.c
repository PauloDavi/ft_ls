/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_entry.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobli <cobli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 11:22:09 by cobli             #+#    #+#             */
/*   Updated: 2025/03/30 23:51:38 by cobli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <grp.h>
#include <linux/limits.h>
#include <pwd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

#include "ft_ls.h"

static void get_link_information(t_entry *entry, const char *path);
static void get_user_and_group_information(t_entry *entry, const struct stat file_stat);
static void get_time_information(t_entry *entry, const struct stat file_stat);
static void get_permissions(mode_t mode, char *perm);
static void concat_paths(char *dest, const char *path, const char *filename);

t_entry *create_entry(const char *path, const char *filename) {
  struct stat file_stat;
  char full_path[PATH_MAX];

  if (path == NULL) {
    ft_memcpy(full_path, filename, ft_strlen(filename) + 1);
  } else {
    concat_paths(full_path, path, filename);
  }
  if (lstat(full_path, &file_stat) < 0) return NULL;
  t_entry *entry = malloc(sizeof(t_entry));
  if (!entry) return NULL;
  ft_memset(entry, 0, sizeof(t_entry));

  entry->name = ft_strdup(filename);
  entry->nlink = file_stat.st_nlink;
  entry->size = file_stat.st_size;
  entry->blocks = file_stat.st_blocks;

  get_permissions(file_stat.st_mode, entry->permissions);
  get_user_and_group_information(entry, file_stat);
  get_time_information(entry, file_stat);
  if (S_ISLNK(file_stat.st_mode)) {
    get_link_information(entry, full_path);
  }

  return entry;
}

bool add_entry(const char *path, const char *filename, t_list **list) {
  t_entry *entry = create_entry(path, filename);
  if (entry == NULL) {
    perror("malloc");
    ft_lstclear(list, free_entry);
    return false;
  }

  t_list *new_node = ft_lstnew(entry);
  if (new_node == NULL) {
    perror("malloc");
    free_entry(entry);
    ft_lstclear(list, free_entry);
    return false;
  }

  if (list == NULL) {
    *list = new_node;
  } else {
    ft_lstadd_back(list, new_node);
  }

  return true;
}

void free_entry(void *entry) {
  if (entry) {
    free(((t_entry *)entry)->name);
    free(((t_entry *)entry)->owner);
    free(((t_entry *)entry)->group);
    free(((t_entry *)entry)->s_time);
    if (((t_entry *)entry)->link) free(((t_entry *)entry)->link);
    free(entry);
  }
}

static void get_link_information(t_entry *entry, const char *path) {
  char link_target[PATH_MAX];
  ssize_t len = readlink(path, link_target, sizeof(link_target) - 1);
  if (len != -1) {
    link_target[len] = '\0';
    entry->link = ft_strdup(link_target);
  } else {
    entry->link = ft_strdup("?");
  }
}

static void get_user_and_group_information(t_entry *entry, const struct stat file_stat) {
  struct passwd *pw = getpwuid(file_stat.st_uid);
  struct group *gr = getgrgid(file_stat.st_gid);
  entry->owner = ft_strdup(pw ? pw->pw_name : "?");
  entry->group = ft_strdup(gr ? gr->gr_name : "?");
}

static void get_time_information(t_entry *entry, const struct stat file_stat) {
  char *time_str = ctime(&file_stat.st_mtime);
  if (time_str) {
    time_str[16] = '\0';
    entry->s_time = ft_strdup(time_str + 4);
  } else {
    entry->s_time = ft_strdup("?");
  }
  entry->time_sec = file_stat.st_mtim.tv_sec;
  entry->time_nsec = file_stat.st_mtim.tv_nsec;
}

static void concat_paths(char *dest, const char *path, const char *filename) {
  size_t path_len = ft_strlen(path);
  size_t filename_len = ft_strlen(filename);

  if (path_len + filename_len + 2 > PATH_MAX) {
    return;
  }

  ft_memcpy(dest, path, path_len);
  if (path[path_len - 1] != '/') {
    dest[path_len] = '/';
    path_len++;
  }
  ft_memcpy(dest + path_len, filename, filename_len);
  dest[path_len + filename_len] = '\0';
}

static void get_permissions(mode_t mode, char *perm) {
  ft_memcpy(perm, "----------", 11);

  if (S_ISDIR(mode))
    perm[0] = 'd';
  else if (S_ISLNK(mode))
    perm[0] = 'l';
  else if (S_ISCHR(mode))
    perm[0] = 'c';
  else if (S_ISBLK(mode))
    perm[0] = 'b';
  else if (S_ISFIFO(mode))
    perm[0] = 'p';
  else if (S_ISSOCK(mode))
    perm[0] = 's';

  if (mode & S_IRUSR) perm[1] = 'r';
  if (mode & S_IWUSR) perm[2] = 'w';
  if (mode & S_IXUSR) perm[3] = 'x';

  if (mode & S_IRGRP) perm[4] = 'r';
  if (mode & S_IWGRP) perm[5] = 'w';
  if (mode & S_IXGRP) perm[6] = 'x';

  if (mode & S_IROTH) perm[7] = 'r';
  if (mode & S_IWOTH) perm[8] = 'w';
  if (mode & S_IXOTH) perm[9] = 'x';
}
