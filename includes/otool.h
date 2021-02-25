/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 19:30:07 by mmarti            #+#    #+#             */
/*   Updated: 2021/02/25 19:30:09 by mmarti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OTOOL_H
# define OTOOL_H

# include "ft_macho.h"

# define USAGE "ft_otool file1 [file2 ...]"

typedef struct			s_text
{
	const unsigned char	*text;
	size_t				size;
}						t_text;

int						get_text(t_text *buf, t_mach_header *mapped);

#endif
