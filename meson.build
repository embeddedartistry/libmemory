project('libmemory',
	['c', 'cpp'],
	default_options : ['c_std=c11','cpp_std=c++17'])

########################
# Identify Compiler(s) #
########################

native_compiler_id = meson.get_compiler('c', native : true).get_id()

if meson.is_cross_build()
	host_compiler_id = meson.get_compiler('c', native : false).get_id()
endif

######################################
# Import compiler flags and warnings #
######################################

# Get compiler flags, and handle host vs cross builds
if meson.is_cross_build()
	if host_compiler_id == 'clang'
		subdir('build/compiler/clang')
	elif host_compiler_id == 'gcc'
		subdir('build/compiler/gcc')
	endif
else
	if native_compiler_id == 'clang'
		subdir('build/compiler/clang')
	elif native_compiler_id == 'gcc'
		subdir('build/compiler/gcc')
	endif
endif

# compiler_args is defined in build/compiler/<target>/meson.build
# We are the standard library, don't complain about __
add_project_arguments([compiler_args], language: 'c')

subdir('build/ea-stdlib')

#########################
# Process Build Options #
#########################

if get_option('enable-werror') == true
	add_project_arguments('-Werror', language : 'c')
endif

if get_option('enable-pedantic-error') == true
	add_project_arguments('-pedantic-error', language : 'c')
endif

#######################
# Process source tree #
#######################

# Used for local builds - we want the warnings
libmemory_includes = include_directories('include', 'dependencies/lib')

# Used for external builds - treat the headers as system headers
libmemory_system_includes = include_directories('include', 'dependencies/lib', is_system: true)

# Library build definition
subdir('src/')

# Test build definition
subdir('test/')

############################
# Supporting Build Targets #
############################

run_target('docs',
	command: ['doxygen', 'docs/Doxyfile'])

run_target('complexity',
	command: ['tools/complexity_check.sh', '-w'])

run_target('complexity-list',
	command: ['tools/complexity_check.sh'])

run_target('cppcheck',
	command: ['cppcheck',
	# Options
	'--quiet', '--enable=style', '--force',
	# Include Directories
	'-I', meson.current_source_dir() + '/include',
	'-I', meson.current_source_dir() + '/dependencies/lib',
	# Source Directories
	'src', 'test']
)

run_target('cppcheck-xml',
	command: ['tools/cppcheck_xml.sh']
)
