# libmemory src/ meson build

common_files = [
	'aligned_malloc.c',
	'posix_memalign.c'
]

clangtidy_files = files(
	'aligned_malloc.c',
	'malloc_freelist.c',
	'malloc_threadx.c',
	'malloc_freertos.c',
	'posix_memalign.c',
	'malloc_assert.c'
	)

rtos_includes = include_directories('../dependencies/rtos/', is_system: true)
dependency_includes = include_directories('../dependencies/lib')

##################################
# System Already Provides Malloc #
##################################

# Pick up extra functions, but don't redefine malloc
libmemory = static_library(
	'memory',
	[common_files],
	include_directories: libmemory_includes,
	dependencies: libc_dep,
	# Do not built by default if we are a subproject
	build_by_default: (meson.is_subproject() == false)
)

# Pick up extra functions, but don't redefine malloc
libmemory_native = static_library(
	'memory_native',
	[common_files],
	include_directories: libmemory_includes,
	dependencies: libc_native_dep,
	native: true,
	# Do not built by default if we are a subproject
	build_by_default: (meson.is_subproject() == false)
)

# Pick up extra functions, but don't redefine malloc, and don't use external libc
libmemory_hosted = static_library(
	'memory_hosted',
	[common_files],
	include_directories: libmemory_includes,
	# Do not built by default if we are a subproject
	build_by_default: (meson.is_subproject() == false)
)

# Pick up extra functions, but don't redefine malloc, and don't use external libc
libmemory_hosted_native = static_library(
	'memory_hosted_native',
	[common_files],
	include_directories: libmemory_includes,
	native: true,
	# Do not built by default if we are a subproject
	build_by_default: (meson.is_subproject() == false)
)

# Pick up extra functions, but don't redefine malloc
libmemory_dep = declare_dependency(
	link_with: libmemory,
	include_directories: libmemory_system_includes,
)

# Pick up extra functions, but don't redefine malloc
libmemory_native_dep = declare_dependency(
	link_with: libmemory_native,
	include_directories: libmemory_system_includes,
)

# Pick up extra functions, but don't redefine malloc
libmemory_hosted_dep = declare_dependency(
	link_with: libmemory_hosted,
	include_directories: libmemory_system_includes,
)

# Pick up extra functions, but don't redefine malloc, and don't use external libc
libmemory_hosted_native_dep = declare_dependency(
	link_with: libmemory_hosted_native,
	include_directories: libmemory_system_includes,
)

#######################
# Malloc Calls Assert #
#######################

libmemory_assert = static_library('memory_assert',
	[common_files, 'malloc_assert.c'],
	c_args: '-Wno-missing-noreturn',
	include_directories: libmemory_includes,
	dependencies: libc_dep,
	# Do not built by default if we are a subproject
	build_by_default: (meson.is_subproject() == false)
)

libmemory_assert_native = static_library('memory_assert_native',
	[common_files, 'malloc_assert.c'],
	include_directories: libmemory_includes,
	c_args: '-Wno-missing-noreturn',
	dependencies: libc_native_dep,
	native: true,
	# Do not built by default if we are a subproject
	build_by_default: (meson.is_subproject() == false),
)

libmemory_assert_dep = declare_dependency(
	link_with: libmemory_assert,
	include_directories: libmemory_system_includes,
)

libmemory_assert_native_dep = declare_dependency(
	link_with: libmemory_assert_native,
	include_directories: libmemory_system_includes,
)

############
# Freelist #
############

libmemory_freelist = static_library(
	'memory_freelist',
	[common_files, 'malloc_freelist.c'],
	include_directories: [libmemory_includes, dependency_includes],
	dependencies: libc_dep,
	# Do not built by default if we are a subproject
	build_by_default: (meson.is_subproject() == false)
)

libmemory_freelist_native = static_library(
	'memory_freelist_native',
	[common_files, 'malloc_freelist.c'],
	include_directories: [libmemory_includes, dependency_includes],
	dependencies: libc_native_dep,
	native: true,
	# Do not built by default if we are a subproject
	build_by_default: (meson.is_subproject() == false)
)

libmemory_freelist_dep = declare_dependency(
	link_with: libmemory_freelist,
	include_directories: libmemory_system_includes,
)

libmemory_freelist_native_dep = declare_dependency(
	link_with: libmemory_freelist_native,
	include_directories: libmemory_system_includes,
)

###########
# ThreadX #
###########

libmemory_threadx = static_library(
	'memory_threadx',
	[common_files, 'malloc_threadx.c'],
	include_directories: [libmemory_includes, rtos_includes],
	dependencies: libc_dep,
	# Do not built by default if we are a subproject
	build_by_default: (meson.is_subproject() == false)
)

libmemory_threadx_dep = declare_dependency(
	link_with: libmemory_threadx,
	include_directories: libmemory_system_includes,
)

############
# FreeRTOS #
############

libmemory_freertos = static_library(
	'memory_freertos',
	[common_files, 'malloc_freertos.c'],
	include_directories: [libmemory_includes, rtos_includes],
	dependencies: libc_dep,
	# Do not built by default if we are a subproject
	build_by_default: (meson.is_subproject() == false)
)

libmemory_freertos_dep = declare_dependency(
	link_with: libmemory_freertos,
	include_directories: libmemory_system_includes,
)

#########################
# Framework RTOS Malloc #
#########################

libmemory_framework_rtos_dep = declare_dependency(
	sources: files('malloc_framework_rtos.cpp'),
	include_directories: libmemory_system_includes
)
