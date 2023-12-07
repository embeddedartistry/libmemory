project('Embedded Artistry libmemory',
	['c', 'cpp'],
	default_options : [
		'warning_level=3',
		'werror=false',
		# `build.*` options affect `native: true targets`
		# plain options affect `native: false` targets.
		'c_std=c11', 'build.c_std=c11',
		'cpp_std=c++17', 'build.cpp_std=c++17',
		# This project defaults to a release build
		'debug=false',
		'optimization=2',
	],
	license: 'MIT',
	meson_version: '>=0.58.0',
	version: '1.0')

########################
# Identify Compiler(s) #
########################

# Pick up our common compiler variables + desired_*_flags variables
subdir('meson/compiler')
subdir('meson/compiler/c')
subdir('meson/compiler/cpp')

# Add project-wide flags

desired_common_compile_flags += [
	'-Wno-reserved-id-macro'
]

if get_option('enable-pedantic')
	desired_common_compile_flags += '-pedantic'
else
	desired_common_compile_flags += '-Wno-pedantic'
endif

if get_option('enable-pedantic-error')
	desired_common_compile_flags += '-pedantic-error'
endif

compile_settings_list = [
	{'lang': 'c', 'compiler': host_c_compiler, 'flags': desired_c_compile_flags, 'isnative': false},
	{'lang': 'c', 'compiler': native_c_compiler, 'flags': desired_native_c_compile_flags, 'isnative': true},
	{'lang': 'cpp', 'compiler': host_cpp_compiler, 'flags': desired_cpp_compile_flags, 'isnative': false},
	{'lang': 'cpp', 'compiler': native_cpp_compiler, 'flags': desired_native_cpp_compile_flags, 'isnative': true},
]

# Process the compilation flags
subdir('meson/compiler/check-and-apply-flags')

#################
# Build Modules #
#################

# Include reusable build modules here via subdir() calls
subdir('meson/linker/linker-map')
subdir('meson/test/cmocka')

###############
# Subprojects #
###############

c_linked_list = subproject('c-linked-list')
c_linked_list_dep = c_linked_list.get_variable('c_linked_list_dep')

########################
# External libc Option #
########################

# NOTE: External libc dependencies are only used for building the library.
# They are not forwarded through dependencies. You are expected to handle
# That with the rest of your program.

libc_dep = []
libc_native_dep = []

if get_option('use-libc-subproject') == true
	message('Using external libc specified in libc-subproject option.')
	libc_array = get_option('libc-subproject')
	libc_subproject = subproject(libc_array[0])

	libc_dep = libc_subproject.get_variable(libc_array[1])
	# Only pull in include directories + compile arguments
	libc_dep = libc_dep.partial_dependency(includes: true, compile_args: true)

	if libc_array.length() > 2
		libc_native_dep = libc_subproject.get_variable(libc_array[2])
		libc_native_dep = libc_native_dep.partial_dependency(includes: true, compile_args: true)
	endif
endif

#######################
# Process source tree #
#######################

# Add files to this variable if you want them analyzed by clang-tidy
clangtidy_files = []

# Used for local builds - we want the warnings
libmemory_includes = include_directories('include')

# Used for external builds - treat the headers as system headers
libmemory_system_includes = include_directories('include', is_system: true)

# Install headers
subdir('include/')

# Library build definition
subdir('src/')

# Test build definition
subdir('test/')

###################
# Tooling Modules #
###################

# Customization options
doxygen_description = 'Memory library for embedded systems (malloc and friends)'

cppcheck_args = [
	'-i', meson.project_source_root() / 'include',
	# Folders to analyze
	meson.project_source_root() / 'src',
	meson.project_source_root() / 'test',
]

clangformat_additional_targets = [
	meson.project_source_root() / 'include',
]

# Include modules
subdir('meson/analysis/clang-tidy')
subdir('meson/analysis/complexity')
subdir('meson/analysis/cppcheck')
subdir('meson/format')
subdir('meson/docs/doxygen')

#############
# Packaging #
#############

host_pkg_name = 'embeddedartistry_libmemory'
native_pkg_name = host_pkg_name + '_native'

# These macros allow you to simplify the declaration of includes for common
# include paths.
build_root_include = meson.project_build_root() + ':@0@'
src_include = meson.project_build_root() / 'src/:@0@'

host_pkg_files = [
	build_root_include.format('docs'),
	src_include.format('libmemory_assert.a'),
	src_include.format('libmemory_freelist.a'),
	src_include.format('libmemory_freertos.a'),
	src_include.format('libmemory_hosted.a'),
	src_include.format('libmemory_threadx.a'),
]

native_pkg_files = [
	build_root_include.format('docs'),
	src_include.format('*_native.a')
]

# Invoke the package module
subdir('meson/package')
