/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobli <cobli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 18:05:45 by cobli             #+#    #+#             */
/*   Updated: 2025/04/03 22:53:35 by cobli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 16:23:52 by sfranc            #+#    #+#             */
/*   Updated: 2017/04/10 11:21:23 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
#define COLOR_H

/*
** Reset
*/
#define RESET "\033[0m"

/*
** Regular
*/
#define BLACK "\033[0;30m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN "\033[0;36m"
#define WHITE "\033[0;37m"

/*
** Bold
*/
#define BBLACK "\033[01;30m"
#define BRED "\033[01;31m"
#define BGREEN "\033[01;32m"
#define BYELLOW "\033[01;33m"
#define BBLUE "\033[01;34m"
#define BMAGENTA "\033[01;35m"
#define BCYAN "\033[01;36m"
#define BWHITE "\033[01;37m"

/*
** Underline
*/
#define UBLACK "\033[4;30m"
#define URED "\033[4;31m"
#define UGREEN "\033[4;32m"
#define UYELLOW "\033[4;33m"
#define UBLUE "\033[4;34m"
#define UMAGENTA "\033[4;35m"
#define UCYAN "\033[4;36m"
#define UWHITE "\033[4;37m"

/*
** Background
*/
#define BGBLACK "\033[40m"
#define BGRED "\033[41m"
#define BGGREEN "\033[42m"
#define BGYELLOW "\033[43m"
#define BGBLUE "\033[44m"
#define BGMAGENTA "\033[45m"
#define BGCYAN "\033[46m"
#define BGWHITE "\033[47m"

#define YELLOW_BLACKBG "\033[40;33m"
#define YELLOW_BLACKBG_BOLD "\033[40;33;01m"
#define WHITE_REDBG "\033[37;41m"
#define BLACK_YELLOWBG "\033[30;43m"
#define BLACK_GREENBG "\033[30;42m"
#define BLUE_GREENBG "\033[34;42m"
#define WHITE_BLUEBG "\033[37;44m"

#endif
