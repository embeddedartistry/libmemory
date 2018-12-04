# libmemory src/ meson build

common_files = [
	'aligned_malloc.c',
]

libmemory_lint_files = files(
	'aligned_malloc.c',
	'malloc_freelist.c',
	'malloc_threadx.c',
	'malloc_freertos.c'
	)

rtos_includes = include_directories('../dependencies/rtos/', is_system: true)

############
# Freelist #
############

libmemory_freelist = static_library(
	'memory_freelist',
	[common_files, 'malloc_freelist.c'],
	# c_args: [stdlib_compiler_flags],
	include_directories: [libmemory_includes]
)

libmemory_freelist_native = static_library(
	'memory_freelist_native',
	[common_files, 'malloc_freelist.c'],
	# c_args: [stdlib_compiler_flags],
	include_directories: [libmemory_includes],
	native: true
)

libmemory_freelist_dep = declare_dependency(
	link_with: libmemory_freelist,
	include_directories: [libmemory_system_includes],
	compile_args: stdlib_compiler_flags,
)

libmemory_freelist_native_dep = declare_dependency(
	link_with: libmemory_freelist_native,
	include_directories: [libmemory_system_includes],
	#compile_args: stdlib_compiler_flags,
)

###########
# ThreadX #
###########

libmemory_threadx = static_library(
	'memory_threadx',
	[common_files, 'malloc_threadx.c'],
	# c_args: [stdlib_compiler_flags],
	include_directories: [libmemory_includes, rtos_includes]
)

libmemory_threadx_dep = declare_dependency(
	link_with: libmemory_threadx,
	include_directories: [libmemory_system_includes],
	compile_args: stdlib_compiler_flags,
)

############
# FreeRTOS #
############

libmemory_freertos = static_library(
	'memory_freertos',
	[common_files, 'malloc_freertos.c'],
	c_args: [
		#stdlib_compiler_flags
	],
	include_directories: [libmemory_includes, rtos_includes]
)

libmemory_freertos_dep = declare_dependency(
	link_with: libmemory_freertos,
	include_directories: [libmemory_system_includes],
	compile_args: stdlib_compiler_flags,
)
