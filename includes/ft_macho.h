#ifndef FT_MACHO_H
# define FT_MACHO_H

# include <mach-o/loader.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/mman.h>
# include <sys/stat.h>

# include "libft.h"

typedef enum	e_file_type
{
	none = 0,
	archx64 = MH_MAGIC_64,
	archx86 = MH_MAGIC
}				t_file_type;

off_t			g_cfsize;
t_file_type		g_file_type;

typedef struct mach_header	t_mach_header;
typedef struct load_command t_load_command;

void	*ft_mmap(char *filename);

#endif