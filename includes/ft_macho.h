#ifndef FT_MACHO_H
# define FT_MACHO_H

# include <mach-o/loader.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/mman.h>
# include <sys/stat.h>
#include <mach-o/fat.h>
# include <ar.h>

# include "ft_printf.h"

# ifdef __i386__
#define G_CPU = CPU_TYPE_X86
# elif __x86_64__
#define G_CPU CPU_TYPE_X86_64
# else
#define G_CPU -1
#endif


typedef enum	e_file_type
{
	fat = FAT_MAGIC,
	archx64 = MH_MAGIC_64,
	archx86 = MH_MAGIC
}				t_file_type;

off_t			g_cfsize;
t_file_type		g_file_type;

typedef struct mach_header	t_mach_header;
typedef struct load_command t_load_command;

void	*ft_mmap(char *filename);

#endif