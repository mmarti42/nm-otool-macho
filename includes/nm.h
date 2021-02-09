#ifndef NM_H
# define NM_H

# include <fcntl.h>
# include <errno.h>
# include <sys/mman.h>
# include <sys/stat.h>

# include "libft.h"
# include "ft_printf.h"
# include <mach-o/loader.h>
# include <mach-o/nlist.h>

# define USAGE "nm [-pruA] [objfile]"

typedef struct	s_opt {
	t_bool p;
	t_bool r;
	t_bool u;
	t_bool a;
}				t_opt;

typedef struct	s_symbol
{
	char			type;
	uint64_t		addr;
	const char		*name;
	struct s_symbol *next;
	struct s_symbol *prev;
}					t_symbol;

typedef enum	e_file_type
{
	none = 0,
	archx64 = MH_MAGIC_64,
	archx86 = MH_MAGIC
}				t_file_type;

typedef struct mach_header	t_mach_header;
typedef struct load_command t_load_command;
typedef struct symtab_command t_symtab_command;
typedef struct nlist t_nlist;
typedef struct nlist_64 t_nlist_64;

t_opt			g_opt;
t_file_type		g_file_type;

void		fatal_err(const char *mes);
void		*xmalloc(size_t size);
t_symbol	*fill_sym_list64(t_nlist_64 *syms, char *strtab, size_t i, char *mapped);
void		*get_lc(uint32_t cmd, t_mach_header *mapped);
t_symbol	*insert_sym(t_symbol *new, t_symbol *first);
char		**ft_nm_getopt(const char **av);


#endif
