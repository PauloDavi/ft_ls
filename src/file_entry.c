/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_entry.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdavi-al <pdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 11:22:09 by cobli             #+#    #+#             */
/*   Updated: 2025/06/22 13:33:06 by pdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <grp.h>
#include <linux/limits.h>
#include <pwd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <time.h>
#include <unistd.h>

#include "ft_ls.h"

/**
 * @brief Get link information for a symbolic link entry.
 * @param entry Pointer to the entry struct
 * @param path Path to the symlink
 */
static void get_link_information(t_entry *entry, const char *path);

/**
 * @brief Get user and group information for an entry.
 * @param entry Pointer to the entry struct
 * @param file_stat Pointer to the stat struct
 */
static void get_user_and_group_information(t_entry *entry, const struct stat *file_stat);

/**
 * @brief Get time information for an entry (modification or access time).
 * @param entry Pointer to the entry struct
 * @param file_stat Pointer to the stat struct
 * @param flags Pointer to the flags struct
 */
static void get_time_information(t_entry *entry, const struct stat *file_stat, const t_flags *flags);

/**
 * @brief Get permissions string for a file mode.
 * @param mode File mode
 * @param perm Output permissions string
 */
static void get_permissions(mode_t mode, char *perm);

/**
 * @brief Initialize a t_entry struct from stat and path info.
 * @param file_stat Pointer to the stat struct
 * @param filename File name
 * @param full_path Full path to the file
 * @param flags Pointer to the flags struct
 * @return Pointer to the allocated t_entry, or NULL on error
 */
static t_entry *init_entry(const struct stat *file_stat, const char *filename, const char *full_path, const t_flags *flags);

/**
 * @brief Check if a file has ACL attributes.
 * @param path File path
 * @return true if has ACL, false otherwise
 */
static bool has_acl(const char *path);

/**
 * @brief Create a t_entry for a given file or directory.
 * @param path Directory path or NULL
 * @param filename File name
 * @param flags Pointer to the flags struct
 * @return Pointer to the allocated t_entry, or NULL on error
 */
t_entry *create_entry(const char *path, const char *filename, const t_flags *flags) {
  struct stat file_stat;
  char full_path[PATH_MAX];

  if (path == NULL) {
    ft_memcpy(full_path, filename, ft_strlen(filename) + 1);
  } else {
    concat_paths(full_path, path, filename);
  }

  if (lstat(full_path, &file_stat) < 0) {
    perror("lstat");
    return (NULL);
  }

  return (init_entry(&file_stat, filename, full_path, flags));
}

/**
 * @brief Add a t_entry to a list, creating and allocating it.
 * @param path Directory path or NULL
 * @param filename File name
 * @param list Pointer to the list
 * @param flags Pointer to the flags struct
 * @return true on success, false on allocation error
 */
bool add_entry(const char *path, const char *filename, t_list **list, const t_flags *flags) {
  t_entry *entry = create_entry(path, filename, flags);
  if (entry == NULL) {
    perror("malloc");
    ft_lstclear(list, free_entry);
    return (false);
  }

  t_list *new_node = ft_lstnew(entry);
  if (new_node == NULL) {
    perror("malloc");
    free_entry(entry);
    ft_lstclear(list, free_entry);
    return (false);
  }

  ft_lstadd_front(list, new_node);
  return (true);
}

/**
 * @brief Free a t_entry and its associated memory.
 * @param entry Pointer to the entry to free
 */
void free_entry(void *entry) {
  if (entry == NULL) return;

  t_entry *e = (t_entry *)entry;
  free(e->name);
  free(e->owner);
  free(e->group);
  free(e->s_time);
  if (e->link) {
    free(e->link->name);
    free(e->link);
  }
  free(e);
}

static t_entry *init_entry(const struct stat *file_stat, const char *filename, const char *full_path, const t_flags *flags) {
  t_entry *entry = malloc(sizeof(t_entry));
  if (!entry) {
    perror("malloc");
    return (NULL);
  }

  ft_memset(entry, 0, sizeof(t_entry));
  entry->name = ft_strdup(filename);
  if (!entry->name) {
    perror("malloc");
    free(entry);
    return (NULL);
  }

  entry->nlink = file_stat->st_nlink;
  entry->size = file_stat->st_size;
  entry->blocks = file_stat->st_blocks;
  entry->mode = file_stat->st_mode;
  entry->is_executable = (file_stat->st_mode & S_IXUSR) || (file_stat->st_mode & S_IXGRP) || (file_stat->st_mode & S_IXOTH);
  entry->is_special = S_ISCHR(file_stat->st_mode) || S_ISBLK(file_stat->st_mode);

  if (entry->is_special) {
    entry->major = major(file_stat->st_rdev);
    entry->minor = minor(file_stat->st_rdev);
  }

  get_permissions(file_stat->st_mode, entry->permissions);
  if (has_acl(full_path)) {
    entry->permissions[10] = '+';
  }

  get_user_and_group_information(entry, file_stat);
  get_time_information(entry, file_stat, flags);

  if (S_ISLNK(file_stat->st_mode)) {
    get_link_information(entry, full_path);
  }

  return (entry);
}

static void get_link_information(t_entry *entry, const char *path) {
  char link_target[PATH_MAX];
  ssize_t len = readlink(path, link_target, sizeof(link_target) - 1);
  link_target[len] = '\0';
  entry->link = malloc(sizeof(t_link));
  ft_memset(entry->link, 0, sizeof(t_link));
  if (len != -1) {
    entry->link->name = ft_strdup(link_target);

    struct stat link_stat;
    if (stat(link_target, &link_stat) == 0) {
      entry->link->mode = link_stat.st_mode;
      entry->link->exist = true;
      entry->link->is_executable = (link_stat.st_mode & S_IXUSR) || (link_stat.st_mode & S_IXGRP) || (link_stat.st_mode & S_IXOTH);
    } else {
      entry->link->exist = false;
    }
  } else {
    entry->link->name = ft_strdup("?");
  }
}

static void get_user_and_group_information(t_entry *entry, const struct stat *file_stat) {
  struct passwd *pw = getpwuid(file_stat->st_uid);
  struct group *gr = getgrgid(file_stat->st_gid);

  entry->owner = ft_strdup(pw ? pw->pw_name : "?");
  entry->group = ft_strdup(gr ? gr->gr_name : "?");
}

static void get_time_information(t_entry *entry, const struct stat *file_stat, const t_flags *flags) {
  time_t time = flags->access ? file_stat->st_atime : file_stat->st_mtime;
  struct timespec tim = flags->access ? file_stat->st_atim : file_stat->st_mtim;

  char *time_str = ctime(&time);
  if (time_str) {
    time_str[16] = '\0';
    entry->s_time = ft_strdup(time_str + 4);
  } else {
    entry->s_time = ft_strdup("?");
  }

  entry->time_sec = tim.tv_sec;
  entry->time_nsec = tim.tv_nsec;
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
  if (mode & S_IXUSR && !S_ISCHR(mode) && !S_ISBLK(mode)) {
    perm[3] = (mode & S_ISUID ? 's' : 'x');
  } else if (mode & S_ISUID) {
    perm[3] = 'S';
  }

  if (mode & S_IRGRP) perm[4] = 'r';
  if (mode & S_IWGRP) perm[5] = 'w';
  if (mode & S_IXGRP && !S_ISCHR(mode) && !S_ISBLK(mode)) {
    perm[6] = (mode & S_ISGID ? 's' : 'x');
  } else if (mode & S_ISGID) {
    perm[6] = 'S';
  }

  if (mode & S_IROTH) perm[7] = 'r';
  if (mode & S_IWOTH) perm[8] = 'w';
  if (mode & S_IXOTH && !S_ISCHR(mode) && !S_ISBLK(mode)) {
    perm[9] = (mode & S_ISVTX ? 't' : 'x');
  } else if (mode & S_ISVTX) {
    perm[9] = 'T';
  }
}

static bool has_acl(const char *path) {
  char buff[255];
  int size = listxattr(path, buff, 255);
  if (size <= 0) {
    return (false);
  }

  char *attr = buff;
  while (attr < buff + size) {
    if (ft_strlen(attr)) {
      return (true);
    }
    attr += ft_strlen(attr) + 1;
  }
  return (false);
}
