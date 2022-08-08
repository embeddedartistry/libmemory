#include <aligned_malloc.h>
#include <assert.h>
#include <errno.h>
#include <stddef.h>

#define IS_POWER_2(x) (!((x) & ((x)-1)))

int posix_memalign(void** __memptr, size_t __alignment, size_t __size)
{
	int return_code = ENOMEM;

	assert(__memptr);
	assert(__size > 0);

	// TODO: Do we need to check if __alignment is a multiple of sizeof(void *)?
	if(!IS_POWER_2(__alignment))
	{
		return_code = EINVAL;
	}
	else
	{
		*__memptr = aligned_malloc(__alignment, __size);

		if(*__memptr != NULL)
		{
			return_code = 0;
		}
	}

	return return_code;
}
