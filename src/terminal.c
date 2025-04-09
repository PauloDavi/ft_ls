/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobli <cobli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 19:20:13 by cobli             #+#    #+#             */
/*   Updated: 2025/04/08 22:57:06 by cobli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <unistd.h>

#include "ft_ls.h"

#define MAX_FILES 1024

static size_t get_terminal_width();
static t_list **convert_list_to_array(t_list *list, size_t size);
static size_t calculate_columns(size_t size, size_t term_width, size_t *col_widths, t_list **array, const t_flags *flags);
static void print_row(size_t row, size_t cols, size_t rows, size_t size, t_list **array, size_t *col_widths, const t_flags *flags);

void print_columns(t_list *list, const t_flags *flags) {
  size_t term_width = get_terminal_width();
  size_t size = ft_lstsize(list);

  t_list **array = convert_list_to_array(list, size);
  if (!array) {
    perror("malloc");
    return;
  }

  size_t col_widths[MAX_FILES];
  size_t cols = calculate_columns(size, term_width, col_widths, array, flags);
  size_t rows = (size + cols - 1) / cols;
  for (size_t row = 0; row < rows; row++) {
    print_row(row, cols, rows, size, array, col_widths, flags);
    ft_printf("\n");
  }

  free(array);
}

void print_comma(t_list *list, const t_flags *flags) {
  t_list *current = list;
  size_t term_width = get_terminal_width();
  size_t total_width = 0;

  while (current) {
    bool has_break = false;
    t_entry *entry = (t_entry *)current->content;
    size_t current_width = ft_strlen(entry->name);
    if (flags->comma) current_width += 2;
    if (current->next) current_width += 1;

    if ((total_width + current_width) > term_width) {
      ft_printf("\n");
      has_break = true;
    }

    print_name(entry->name, entry->mode, entry->is_executable, !flags->color, flags->quote_name, 0);

    if (current->next) {
      current_width += 1;
      ft_printf(", ");
    }

    if (has_break) {
      total_width = current_width;
    } else {
      total_width += current_width;
    }

    current = current->next;
  }
  ft_printf("\n");
}

static size_t get_terminal_width() {
  struct winsize w;
  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) return 80;
  return w.ws_col;
}

static t_list **convert_list_to_array(t_list *list, size_t size) {
  t_list **array = malloc(sizeof(t_list *) * size);
  if (!array) return NULL;

  t_list *tmp = list;
  for (size_t i = 0; i < size && tmp; i++) {
    array[i] = tmp;
    tmp = tmp->next;
  }

  return array;
}

static size_t calculate_columns(size_t size, size_t term_width, size_t *col_widths, t_list **array, const t_flags *flags) {
  size_t cols = 0;

  for (cols = size; cols > 0; cols--) {
    size_t rows = (size + cols - 1) / cols;
    size_t total_width = 0;

    for (size_t col = 0; col < cols; col++) {
      size_t max_col_width = 0;

      for (size_t row = 0; row < rows; row++) {
        size_t index = row + col * rows;
        if (index >= size) break;

        size_t len = ft_strlen(((t_entry *)(array[index]->content))->name);
        if (flags->color) len += 2;
        if (len > max_col_width) max_col_width = len;
      }

      col_widths[col] = max_col_width;
      total_width += max_col_width + 2;
    }

    if (total_width - 2 <= term_width) break;
  }

  return cols;
}

static void print_row(size_t row, size_t cols, size_t rows, size_t size, t_list **array, size_t *col_widths, const t_flags *flags) {
  for (size_t col = 0; col < cols; col++) {
    size_t index = row + col * rows;
    if (index >= size) continue;

    size_t pad = (col == cols - 1) ? 0 : 2;
    print_name(
        ((t_entry *)array[index]->content)->name,
        ((t_entry *)array[index]->content)->mode,
        ((t_entry *)array[index]->content)->is_executable,
        !flags->color,
        flags->quote_name,
        col_widths[col] + pad);
  }
}
