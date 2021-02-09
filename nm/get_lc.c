#include "nm.h"

void *get_lc(uint32_t cmd, t_mach_header *mapped)
{
	uint32_t		i;
	t_load_command	*ld;

	i = 0;
	if (g_file_type == archx86)
		ld = (t_load_command *)((char *)mapped + sizeof(struct mach_header));
	else
		ld = (t_load_command *)((char *)mapped + sizeof(struct mach_header_64));
	while (++i <= mapped->ncmds)
	{
		if (ld->cmd == cmd)
			return ld;
		ld = (t_load_command *)((char  *)ld + ld->cmdsize);
	}
	return NULL;
}
