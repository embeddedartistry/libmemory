# libmemory src/ meson build

common_files = [
	'aligned_malloc.c',
]

rtos_includes = include_directories('../dependencies/rtos/')

libmemory_freelist = static_library(
	'memory_freelist',
	[common_files, 'malloc_freelist.c'],
	c_args: [stdlib_compiler_flags],
	include_directories: [libmemory_includes]
)

libmemory_threadx = static_library(
	'memory_threadx',
	[common_files, 'malloc_threadx.c'],
	c_args: [stdlib_compiler_flags],
	include_directories: [libmemory_includes, rtos_includes]
)

libmemory_freertos = static_library(
	'memory_freertos',
	[common_files, 'malloc_freertos.c'],
	c_args: [stdlib_compiler_flags],
	include_directories: [libmemory_includes, rtos_includes]
)
