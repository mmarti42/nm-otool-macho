#ifndef OTOOL_H
#define OTOOL_H

#include "ft_macho.h"

#define USAGE "ft_otool file1 [file2 ...]"

typedef struct	s_text
{
	const char	*text;
	size_t		size;
}				t_text;

#endif