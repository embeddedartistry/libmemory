# libmemory src/ meson build

common_files = [
	'aligned_malloc.c',
	'posix_memalign.c'
]

libmemory_lint_files = files(
	'aligned_malloc.c',
	'malloc_freelist.c',
	'malloc_threadx.c',
	'malloc_freertos.c',
	'posix_memalign.c',
	'malloc_assert.c'
	)

rtos_includes = include_directories('../dependencies/rtos/', is_system: true)
dependency_includes = include_directories('../dependencies/lib')

############
# Freelist #
############

# Pick up extra functions, but don't redefine malloc
libmemory_native = static_library(
	'memory_native',
	[common_files],
	include_directories: [libmemory_includes],
	native: true
)

# Pick up extra functions, but don't redefine malloc
libmemory_hosted = static_library(
	'memory_hosted',
	[common_files],
	include_directories: [libmemory_includes, libc_target_include_directories],
)

libmemory_assert = static_library('memory_assert',
	[common_files, 'malloc_assert.c'],
	c_args: '-Wno-missing-noreturn',
	include_directories: [libmemory_includes, libc_target_include_directories]
)

libmemory_assert_native = static_library('memory_assert_native',
	[common_files, 'malloc_assert.c'],
	include_directories: [libmemory_includes, libc_target_include_directories],
	c_args: '-Wno-missing-noreturn',
	native: true,
)

libmemory_freelist = static_library(
	'memory_freelist',
	[common_files, 'malloc_freelist.c'],
	include_directories: [libmemory_includes, dependency_includes, libc_target_include_directories]
)

libmemory_freelist_native = static_library(
	'memory_freelist_native',
	[common_files, 'malloc_freelist.c'],
	include_directories: [libmemory_includes, dependency_includes],
	native: true
)

# Pick up extra functions, but don't redefine malloc
libmemory_native_dep = declare_dependency(
	link_with: libmemory_native,
	include_directories: [libmemory_system_includes],
)

# Pick up extra functions, but don't redefine malloc
libmemory_hosted_dep = declare_dependency(
	link_with: libmemory_hosted,
	include_directories: [libmemory_system_includes],
)

libmemory_assert_dep = declare_dependency(
	link_with: libmemory_assert,
	include_directories: [libmemory_system_includes],
	compile_args: stdlib_compiler_flags,
)

libmemory_assert_native_dep = declare_dependency(
	link_with: libmemory_assert_native,
	include_directories: [libmemory_system_includes],
)

libmemory_freelist_dep = declare_dependency(
	link_with: libmemory_freelist,
	include_directories: [libmemory_system_includes],
	compile_args: stdlib_compiler_flags,
)

libmemory_freelist_native_dep = declare_dependency(
	link_with: libmemory_freelist_native,
	include_directories: [libmemory_system_includes],
)

###########
# ThreadX #
###########

libmemory_threadx = static_library(
	'memory_threadx',
	[common_files, 'malloc_threadx.c'],
	# c_args: [stdlib_compiler_flags],
	include_directories: [libmemory_includes, rtos_includes, libc_target_include_directories]
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
	include_directories: [libmemory_includes, rtos_includes, libc_target_include_directories]
)

libmemory_freertos_dep = declare_dependency(
	link_with: libmemory_freertos,
	include_directories: [libmemory_system_includes],
	compile_args: stdlib_compiler_flags,
)

#########################
# Framework RTOS Malloc #
#########################

libmemory_framework_rtos_dep = declare_dependency(
	sources: files('malloc_framework_rtos.cpp'),
	compile_args: stdlib_compiler_flags,
	include_directories: libmemory_system_includes
)
