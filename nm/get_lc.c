#include "nm.h"

t_load_command *next_com(t_load_command *ld)
{
	return (t_load_command *)((char *)ld + ld->cmdsize);
}

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
		if ((char *)ld - (char *)mapped + ld->cmdsize >= g_cfsize)
			fatal_err("corrupted");
		if (ld->cmd == cmd)
			return ld;
		ld = next_com(ld);
	}
	return NULL;
}
