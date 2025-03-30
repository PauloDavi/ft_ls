/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tabulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobli <cobli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 16:25:57 by cobli             #+#    #+#             */
/*   Updated: 2025/03/30 16:36:22 by cobli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void calc_tabulation(t_tabulation *tab, t_entry *entry);

t_tabulation find_max_tabulations(t_list *list) {
  t_tabulation tab = {0, 0, 0, 0};
  t_list *current = list;

  while (current) {
    t_entry *entry = (t_entry *)current->content;
    calc_tabulation(&tab, entry);
    current = current->next;
  }

  return tab;
}

static void calc_tabulation(t_tabulation *tab, t_entry *entry) {
  size_t nlink_len = ft_unbrlen(entry->nlink);
  size_t owner_len = ft_strlen(entry->owner);
  size_t group_len = ft_strlen(entry->group);
  size_t size_len = ft_nbrlen(entry->size);

  if (nlink_len > tab->max_nlink)
    tab->max_nlink = nlink_len;
  if (owner_len > tab->max_owner)
    tab->max_owner = owner_len;
  if (group_len > tab->max_group)
    tab->max_group = group_len;
  if (size_len > tab->max_size)
    tab->max_size = size_len;
}
