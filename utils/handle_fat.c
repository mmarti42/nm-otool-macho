/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 20:59:44 by mmarti            #+#    #+#             */
/*   Updated: 2021/02/25 20:59:45 by mmarti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_macho.h"

#ifdef __LITTLE_ENDIAN__

static uint32_t			b_swap32(uint32_t x)
{
	return ((((x) & 0xff000000u) >> 24) | (((x) & 0x00ff0000u) >> 8)
			| (((x) & 0x0000ff00u) << 8) | (((x) & 0x000000ffu) << 24));
}

#else

static uint32_t			b_swap32(uint32_t x)
{
	return (x);
}

#endif

static t_mach_header	*get_header(long num, struct fat_arch *it, void *mapped)
{
	t_mach_header	*ret;

	ret = NULL;
	while (num--)
	{
		if (b_swap32(it->cputype) == G_CPU)
		{
			ret = (t_mach_header *)((char *)mapped + b_swap32(it->offset));
			break ;
		}
		it++;
	}
	if (!ret)
		return (t_mach_header *)((char *)mapped + b_swap32((((struct fat_arch *)
			((char *)mapped + sizeof(struct fat_header)))->offset)));
	else
		return (ret);
}

t_mach_header			*handle_fat(void *mapped)
{
	long			num;
	struct fat_arch	*it;
	t_mach_header	*ret;

	if ((num = (long)b_swap32(((struct fat_header *)mapped)->nfat_arch))
	* 0x1000 > g_cfsize)
		fatal_err("corrupted");
	it = (struct fat_arch *)((char *)mapped + sizeof(struct fat_header));
	if (G_CPU == -1)
		return (t_mach_header *)((char *)mapped + it->offset);
	ret = get_header(num, it, mapped);
	if ((long)ret - (long)mapped >= g_cfsize)
		fatal_err("corrupted");
	g_cfsize -= (char *)ret - (char *)mapped;
	return (ret);
}
