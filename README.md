# Embedded Artistry libmemory

Embedded Artistry's `libmemory` is a memory management library for embedded systems. If you have a bare metal system and want to use `malloc()`, this library is for you!

`libmemory` provides various implementations of the `malloc()` and `free()` functions. The primary `malloc` implementation is a free-list allocator which can be used on a bare-metal system. Wrappers for some RTOSes are also provided (and can be added if not already). You will also find other useful memory functions, such as `aligned_malloc()`.

This library is meant to be coupled with a `libc` implementation (such as the [Embedded Artistry `libc`][1]). `malloc()` and `free()` are not redefined in these headers, so you can safely use this library with your platform's existing `libc`.

## Table of Contents

1. [About the Project](#about-the-project)
2. [Project Status](#project-status)
3. [Getting Started](#getting-started)
	1. [Requirements](#requirements)
	2. [Getting the Source](#getting-the-source)
	3. [Building](#building)
		1. [Cross-compiling](#cross-compiling)
	4. [Installation](#installation)
	5. [Testing](#testing)
5. [Usage](#usage)
	1. [Aligned `malloc`](#aligned-malloc)
4. [Formatting](#formatting)
5. [Documentation](#documentation)
6. [Need Help?](#need-help)
7. [Contributing](#contributing)
8. [Further Reading](#further-reading)
9. [Authors](#authors)
10. [License](#license)
11. [Acknowledgments](#Acknowledgments)


# About the Project

This library is meant to allow developers of embedded systems to utilize the `malloc()` and `free()` functions if their platform does not currently support it. The baseline `malloc()` implementation can be used without an RTOS or any other supporting software. Only a block of memory needs to be assigned.

Many RTOSes provide dynamic memory allocation functionality, but these functions are not typically called `malloc()` and `free()`. Wrappers can be provided for these RTOSes to improve code portability.

A block of memory needs to be initially assigned using the `malloc_addblock()` function. This tells the `malloc` implementation what memory address and size to use for the heap.

```
// Allocate 4MB to the heap starting at memory address 0xDEADBEEF
malloc_addblock(0xDEADBEEF, 4 * 1024 * 1024);
```

One memory has been allocated to the heap, you can use `malloc()` and `free()` as expected.

# Project Status

* Basic memory allocation is implemented using the free-list strategy
* x86, x86_64, ARM, and ARM64 compilation is supported
* Example RTOS implementations are provided for FreeRTOS and ThreadX
* An implementation exists that can be used with the Embedded Virtual Machine framework
* Tests are currently in place for `malloc()`, `free()`, `aligned_malloc()`, and `aligned_free()`
* No test for overlapping memory blocks currently exists

# Getting Started

### Requirements

* [CMocka][3] must be installed on your system to compile and run unit tests
* [Doxygen][0] must be installed to generate documentation
* [Meson](#meson-build-system) is the build system
* [`git-lfs`][7] is used to store binary files in this repository
* `make` is needed if you want to use the Makefile shims
* You'll need some kind of compiler for your target system.
	- This repository has been tested with:
		- gcc
		- arm-none-eabi-gcc
		- Apple clang
		- Mainline clang


Contributors will also need:

* [`adr-tools`](https://github.com/npryce/adr-tools) for documenting major project decisions
* [`clang-format`][2] for code formatting

#### git-lfs

This project stores some files using [`git-lfs`](https://git-lfs.github.com).

To install `git-lfs` on Linux:

```
sudo apt install git-lfs
```

To install `git-lfs` on OS X:

```
brew install git-lfs
```

Additional installation instructions can be found on the [`git-lfs` website](https://git-lfs.github.com).

#### Meson Build System

The [Meson][meson] build system depends on `python3` and `ninja-build`.

To install on Linux:

```
sudo apt-get install python3 python3-pip ninja-build
```

To install on OSX:

```
brew install python3 ninja
```

Meson can be installed through `pip3`:

```
pip3 install meson
```

If you want to install Meson globally on Linux, use:

```
sudo -H pip3 install meson
```

#### `adr-tools`

This repository uses [Architecture Decision Records](https://embeddedartistry.com/blog/2018/4/5/documenting-architectural-decisions-within-our-repositories). Please install [`adr-tools`](https://github.com/npryce/adr-tools) to contribute to architecture decisions.

If you are using OSX, you can install `adr-tools` through Homebrew:

```
brew install adr-tools
```

If you are using Windows or Linux, please install `adr-tools` via [GitHub](https://github.com/npryce/adr-tools).

### Getting the Source

This project uses [`git-lfs`](https://git-lfs.github.com), so please install it before cloning. If you cloned prior to installing `git-lfs`, simply run `git lfs pull` after installation.

This project is [hosted on GitHub][8]. You can clone the project directly using this command:

```
git clone --recursive git@github.com:embeddedartistry/libmemory.git
```

If you don't clone recursively, be sure to run the following command in the repository or your build will fail:

```
git submodule update --init
```

### Building

The library can be built by issuing the following command:

```
make
```

This will build all targets for your current architecture.

You can clean builds using:

```
make clean
```

You can eliminate the generated `buildresults` folder using:

```
make purify
```

You can also use the `meson` method for compiling.

Create a build output folder:

```
meson buildresults
```

Then change into that folder and build targets by running:

```
ninja
```

At this point, `make` would still work.

#### Cross-compiling

Cross-compilation is handled using `meson` cross files. Example files are included in the [`build/cross`](build/cross/) folder. You can write your own cross files for your specific platform (or open an issue and we can help you).

Cross-compilation must be configured using the meson command when creating the build output folder. For example:

```
meson buildresults --cross-file build/cross/gcc/arm/gcc_arm_cortex-m4.txt
```

Following that, you can run `make` (at the project root) or `ninja` (within the build output directory) to build the project.

Tests will not be cross-compiled. They will be built for the native platform.
### Installation

If you don't use `meson` for your project, the best method to use this project is to build it separately and copy the headers and library contents into your source tree.

* Copy the `include/` directory contents into your source tree.
* Library artifacts are stored in the `buildresults/src` folder
* Copy the desired library to your project and add the library to your link step.

Example linker flags:

```
-Lpath/to/libmemory.a -lmemory
```

If you're using `meson`, you can use `libmemory` as a subproject. Place it into your subproject directory of choice and add a `subproject` statement:

```
libmemory = subproject('libmemory')
```

You will need to promote the subproject dependencies to your project:

```
libmemory_native_dep = libmemory.get_variable('libmemory_native_dep')
libmemory_hosted_dep = libmemory.get_variable('libmemory_hosted_dep')
libmemory_freelist_dep = libmemory.get_variable('libmemory_freelist_dep')
libmemory_threadx_dep = libmemory.get_variable('libmemory_threadx_dep')
libmemory_freertos_dep = libmemory.get_variable('libmemory_freertos_dep')
libmemory_header_include =  libmemory.get_variable('libmemory_system_includes')
libmemory_framework_rtos_dep = libmemory.get_variable('libmemory_framework_rtos_dep')
```

You can use the dependency for your target library configuration in your `executable` declarations(s) or other dependencies. For example:

```
fwdemo_sim_platform_dep = declare_dependency(
	include_directories: fwdemo_sim_platform_inc,
	dependencies: [
		fwdemo_simulator_hw_platform_dep,
		posix_os_dep,
		libmemory_native_dep, # <----- libmemory added here
		libc_native_dep, 
		libcxxabi_native_dep,
		libcxx_full_native_dep,
		logging_subsystem_dep
	],
	sources: files('platform.cpp'),
)
```

## Testing

The tests for this library are written with [CMocka][3]. You can run the tests by issuing the following command:

```
make test
```

By default, test results are generated for use by the CI server and are formatted in JUnit XML. The test results XML files can be found in `buildresults/test/`.

## Usage

A block of memory needs to be initially assigned using the `malloc_addblock()` function:

```
void malloc_addblock(void* addr, size_t size);
```


This tells the `malloc` implementation what memory address and size to use for the heap.

```
// Allocate 4MB to the heap starting at memory address 0xDEADBEEF
malloc_addblock(0xDEADBEEF, 4 * 1024 * 1024);
```

`malloc()` and `free()` will fail (return `NULL`) if no memory has been allocated. Once memory has been allocated to the heap, you can use `malloc()` and `free()` as expected.

Multiple blocks of memory can be added using `malloc_addblock()`. The memory blocks do not have to be contiguous.

### Aligned malloc

You can allocate aligned memory using `aligned_malloc()`:

```
void* aligned_malloc(size_t align, size_t size);
```

Alignment must be a power of two!

Aligned memory can only be free'd using `aligned_free()`:

```
void aligned_free(void* ptr);
```

For more information, see `aligned_memory.h`and [the documentation][10].

# Formatting

This repository enforces formatting using [`clang-format`][2].

You can auto-format your code to match the style guidelines by issuing the following command:

```
make format
```

Formatting is enforced by the Jenkins build server which runs continuous integration for this project. Your pull request will not be accepted if the formatting check fails.

# Documentation

[Documentation for the latest release can always be found here][9].

Documentation can be built locally by running the following command:

```
make docs
```

Documentation can be found in `buildresults/doc`, and the root page is `index.html`.

# Need help?

If you need further assistance or have any questions, please [file a GitHub Issue][6] or send us an email using the [Embedded Artistry Contact Form][5].

You can also reach out on Twitter: [\@mbeddedartistry](https://twitter.com/mbeddedartistry/).

# Contributing

If you are interested in contributing to this project, please read our [contributing guidelines](docs/CONTRIBUTING.md).

# Further Reading

* [`libmemory` Documentation][9]
* [CONTRIBUTING guide](docs/CONTRIBUTING.md)

# Authors

* **[Phillip Johnston](https://github.com/phillipjohnston)** - original library author - [Embedded Artistry](https://github.com/embeddedartistry)

# License

Copyright (c) 2017 Embedded Artistry LLC

This project is licensed under the MIT License - see [LICENSE](LICENSE) file for details.

# Acknowledgments

**[Back to top](#table-of-contents)**

[0]: http://www.stack.nl/~dimitri/doxygen/
[1]: https://github.com/embeddedartistry/libc
[2]: https://clang.llvm.org/docs/ClangFormat.html
[3]: https://cmocka.org
[4]: https://github.com/premake/premake-core/wiki
[5]: http://embeddedartistry.com/contact
[6]: https://github.com/embeddedartistry/libmemory/issues/new
[7]: https://git-lfs.github.com
[8]: https://github.com/embeddedartistry/libmemory
[9]: https://embeddedartistry.github.io/libmemory/index.html
[10]: https://embeddedartistry.github.io/libmemory/d6/dfa/aligned__malloc_8h.html
