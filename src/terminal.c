/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdavi-al <pdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 19:20:13 by cobli             #+#    #+#             */
/*   Updated: 2025/06/22 13:37:41 by pdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <unistd.h>

#include "ft_ls.h"

#define MAX_FILES 1024

/**
 * @brief Get the width of the terminal in columns.
 * @return Number of columns (default 80 if unknown)
 */
static size_t get_terminal_width();

/**
 * @brief Convert a linked list to an array of pointers for easier column printing.
 * @param list List to convert
 * @param size Number of elements
 * @return Array of pointers to list nodes
 */
static t_list **convert_list_to_array(t_list *list, size_t size);

/**
 * @brief Calculate the number of columns and column widths for printing.
 * @param size Number of elements
 * @param term_width Terminal width
 * @param col_widths Output array for column widths
 * @param array Array of list nodes
 * @param flags Flags struct
 * @return Number of columns
 */
static size_t calculate_columns(size_t size, size_t term_width, size_t *col_widths, t_list **array, const t_flags *flags);

/**
 * @brief Print a single row of entries in column format.
 * @param row Row index
 * @param cols Number of columns
 * @param rows Number of rows
 * @param size Total number of entries
 * @param array Array of list nodes
 * @param col_widths Array of column widths
 * @param flags Flags struct
 */
static void print_row(size_t row, size_t cols, size_t rows, size_t size, t_list **array, size_t *col_widths, const t_flags *flags);

/**
 * @brief Print a single entry with a comma, for comma-separated output.
 * @param entry Entry to print
 * @param flags Flags struct
 * @param is_last Whether this is the last entry
 */
static void print_entry_with_comma(const t_entry *entry, const t_flags *flags, bool is_last);

/**
 * @brief Determine if a line break is needed for comma-separated output.
 * @param total_width Current line width
 * @param current_width Width of the next entry
 * @param term_width Terminal width
 * @return true if a break is needed, false otherwise
 */
static bool should_break_line(size_t total_width, size_t current_width, size_t term_width);

/**
 * @brief Print a list of entries in columns, fitting the terminal width.
 * @param list List of entries
 * @param flags Flags struct
 */
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

/**
 * @brief Print a list of entries as a comma-separated list, wrapping as needed.
 * @param list List of entries
 * @param flags Flags struct
 */
void print_comma(t_list *list, const t_flags *flags) {
  t_list *current = list;
  size_t term_width = get_terminal_width();
  size_t total_width = 0;

  while (current) {
    t_entry *entry = (t_entry *)current->content;

    size_t current_width = ft_strlen(entry->name);
    if (flags->comma) current_width += 2;
    if (current->next) current_width += 1;

    if (should_break_line(total_width, current_width, term_width)) {
      ft_printf("\n");
      total_width = 0;
      current_width += 1;
    }

    print_entry_with_comma(entry, flags, current->next == NULL);
    total_width += current_width;
    current = current->next;
  }

  ft_printf("\n");
}

static void print_entry_with_comma(const t_entry *entry, const t_flags *flags, bool is_last) {
  print_name(entry->name, entry->mode, entry->is_executable, !flags->color, flags->quote_name, 0);
  if (!is_last) {
    ft_printf(", ");
  }
}

static bool should_break_line(size_t total_width, size_t current_width, size_t term_width) {
  return (total_width + current_width) > term_width;
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
