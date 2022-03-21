# libmemory test build definition

clangtidy_files += files(
	'main.c',
	'main_locking.c',
	'support/memory.c',
	'src/aligned_malloc.c',
	'src/malloc_freelist.c',
	'src/malloc_freelist_locking.c'
)

libmemory_freelist_tests = executable('libmemory_freelist_test',
	sources: [
		'main.c',
		'support/memory.c',
		'src/aligned_malloc.c',
		'src/malloc_freelist.c'
	],
	c_args: [
		'-Wno-vla',
		'-Wno-unused-parameter',
		'-O0',
		'-DALIGNED_MALLOC_CHECK_LARGE_ALLOC',
	],
	dependencies: [
		cmocka_native_dep,
		libmemory_freelist_native_dep,
		libc_native_dep,
	],
	native: true,
	# Do not built by default if we are a subproject
	build_by_default: (meson.is_subproject() == false),
)

libmemory_freelist_locking_tests = executable('libmemory_freelist_locking_tests',
	sources: [
		'main_locking.c',
		'support/memory.c',
		'src/malloc_freelist_locking.c'
	],
	c_args: [
		'-Wno-vla',
		'-Wno-unused-parameter',
		'-O0',
		'-DALIGNED_MALLOC_CHECK_LARGE_ALLOC',
	],
	dependencies: [
		cmocka_native_dep,
		libmemory_freelist_native_dep,
		libc_native_dep,
	],
	native: true,
	# Do not built by default if we are a subproject
	build_by_default: (meson.is_subproject() == false),
)

#############################
# Register Tests with Meson #
#############################

test_output_dir = 'CMOCKA_XML_FILE=' + meson.build_root() + '/test/%g.xml'

if meson.is_subproject() == false
	test('libmemory_freelist_tests',
		libmemory_freelist_tests,
		env: [ test_output_dir ])

	test('libmemory_freelist_locking_tests',
		libmemory_freelist_locking_tests,
		env: [ test_output_dir ])
endif
