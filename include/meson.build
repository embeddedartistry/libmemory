cp = find_program('cp')

libmemory_install_headers = files(
	'aligned_malloc.h',
	'malloc.h'
)

install_libmemory_headers = custom_target('install-libmemory-headers',
	input: libmemory_install_headers,
	output: 'aligned_malloc.h',
	command: [
		cp, '@INPUT@', meson.current_build_dir()
	],
	build_by_default: true
)
