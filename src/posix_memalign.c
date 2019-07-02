#include <aligned_malloc.h>
#include <assert.h>
#include <errno.h>
#include <stddef.h>

#define IS_POWER_2(x) (!((x) & ((x)-1)))

int posix_memalign(void** __memptr, size_t __alignment, size_t __size)
{
	int r = ENOMEM;

	assert(__memptr);
	assert(__size > 0);

	// TODO: Do we need to check if __alignment is a multiple of sizeof(void *)?
	if(!IS_POWER_2(__alignment))
	{
		r = EINVAL;
	}
	else
	{
		*__memptr = aligned_malloc(__alignment, __size);

		if(*__memptr != NULL)
		{
			r = 0;
		}
	}

	return r;
}
