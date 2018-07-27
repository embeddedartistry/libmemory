# libmemory src/ meson build

common_files = [
	'aligned_malloc.c',
]

rtos_includes = include_directories('../dependencies/rtos/')

############
# Freelist #
############

libmemory_freelist = static_library(
	'memory_freelist',
	[common_files, 'malloc_freelist.c'],
	c_args: [stdlib_compiler_flags],
	include_directories: [libmemory_includes]
)

if meson.is_cross_build()
	libmemory_freelist_native = static_library(
		'memory_freelist_native',
		[common_files, 'malloc_freelist.c'],
		c_args: [stdlib_compiler_flags],
		include_directories: [libmemory_includes]
	)
endif

libmemory_freelist_dep = declare_dependency(
	link_with: libmemory_freelist,
	include_directories: [libmemory_includes],
	compile_args: stdlib_compiler_flags,
)

###########
# ThreadX #
###########

libmemory_threadx = static_library(
	'memory_threadx',
	[common_files, 'malloc_threadx.c'],
	c_args: [stdlib_compiler_flags],
	include_directories: [libmemory_includes, rtos_includes]
)

libmemory_threadx_dep = declare_dependency(
	link_with: libmemory_threadx,
	include_directories: [libmemory_includes],
	compile_args: stdlib_compiler_flags,
)

############
# FreeRTOS #
############

libmemory_freertos = static_library(
	'memory_freertos',
	[common_files, 'malloc_freertos.c'],
	c_args: [stdlib_compiler_flags],
	include_directories: [libmemory_includes, rtos_includes]
)

libmemory_freertos_dep = declare_dependency(
	link_with: libmemory_freertos,
	include_directories: [libmemory_includes],
	compile_args: stdlib_compiler_flags,
)
