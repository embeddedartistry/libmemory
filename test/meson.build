# libmemory test build definition

libmemory_freelist_test_files = files(
	'main.c',
	'support/memory.c',
	'src/aligned_malloc.c',
	'src/malloc_freelist.c'
)

libmemory_freelist_tests = executable('libmemory_freelist_test',
	libmemory_freelist_test_files,
	c_args: ['-Wno-vla', '-Wno-unused-parameter', '-O0'],
	dependencies: [cmocka_native_dep, libmemory_freelist_native_dep],
	native: true
)

#############################
# Register Tests with Meson #
#############################

test_output_dir = 'CMOCKA_XML_FILE=' + meson.build_root() + '/test/%g.xml'

test('libmemory_freelist_tests',
	libmemory_freelist_tests,
	env: [ test_output_dir ])
