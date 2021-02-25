/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 19:32:45 by mmarti            #+#    #+#             */
/*   Updated: 2021/02/25 19:32:48 by mmarti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include "ft_macho.h"
# include <mach-o/nlist.h>

# define USAGE "nm [-pruA] [objfile]"

typedef struct					s_opt {
	t_bool p;
	t_bool r;
	t_bool u;
	t_bool g;
	t_bool aa;
	t_bool print_files;
}								t_opt;

typedef struct					s_symbol
{
	char			type;
	uint64_t		addr;
	const char		*name;
	struct s_symbol *next;
	struct s_symbol *prev;
}								t_symbol;

typedef struct symtab_command	t_symtab_command;
typedef struct nlist			t_nlist;
typedef struct nlist_64			t_nlist_64;

t_opt							g_opt;

void							fatal_err(const char *mes);
void							*xmalloc(size_t size);
t_symbol						*fill_sym_list64(t_nlist_64 *syms,
char *strtab, size_t i, char *mapped);
void							*get_lc(uint32_t cmd, t_mach_header *mapped);
t_symbol						*insert_sym(t_symbol *new, t_symbol *first);
t_load_command					*next_com(t_load_command *ld);
t_symbol						*fill_sym_list32(t_nlist *syms,
char *strtab, size_t i, char *mapped);
void							print_symtab(char *filename);
void							free_sym_list(t_symbol *symlist);

#endif
