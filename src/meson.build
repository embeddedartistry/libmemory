# libmemory src/ meson build

common_files = [
	'aligned_malloc.c',
]

libmemory_freelist = static_library(
	'memory',
	[common_files, 'malloc_freelist.c'],
	c_args: [stdlib_compiler_flags],
	include_directories: [libmemory_includes]
)
