# libmemory

Embedded Artistry's `libmemory` is a memory management library for embedded systems. If you have a bare metal system and want to use `malloc()`, this library is for you!

`libmemory` provides various implemetations of the `malloc()` and `free()` functions. The primary malloc implementation is a freelist allocator which can be used on a bare-metal system. Wrappers for some RTOSes are also provided (and can be added if not already). You wil also find other useful memory functions, such as `aligned_malloc()`.

This library is meant to be coupled with a `libc` implementation (such as the [Embedded Artistry `libc`][1]). `malloc()` and `free()` are not redefined in these headers, so you can safely use this library with your platform's existing `libc`.

## Table of Contents

1. [About the Project](#about-the-project)
2. [Project Status](#project-status)
3. [Getting Started](#getting-started)
	1. [Requirements](#requirements)
	2. [Building](#building)
	3. [Installation](#installation)
	4. [Usage](#usage)
4. [Release Process](#release-process)
	1. [Versioning](#versioning)

# About the Project

This library is meant to allow developers of embedded systems to utilize the `malloc()` and `free()` functions if their platform does not currently support it. The baseline `malloc()` implementation can be used without an RTOS or any other supporting software. Only a block of memory needs to be assigned.

Many RTOSes provide dynamic memory allocation functionality, but these functions are not typically called `malloc()` and `free()`. Wrappers can be provdied for these RTOSes to improve code portability.

A block of memory needs to be initially assigned using the `malloc_addblock()` function. This tells the malloc implementation what memory address and size to use for the heap.

```
// Allocate 4MB to the heap starting at memory address 0xDEADBEEF
malloc_addblock(0xDEADBEEF, 4 * 1024 * 1024);
```

One memory has been allcated to the heap, you can use `malloc()` and `free()` as expected.

# Project Status

* Basic memory allocation is implemented using the free-list strategy
* Cross-compiling with the Premake buildsystem is currently not implemented.
* Only the ThreadX RTOS has currenetly been added
	* FreeRTOS is next on the list
* Tests are currently in place for `malloc()`, `free()`, `aligned_malloc()`, and `aligned_free()`
* The ThreadX malloc implementation is not tested
* No test for overlapping memory blocks exists

# Getting Started

## Requirements

* [Doxygen][0] must be installed to generate documentation
* [Premake][4] is used as the buildsystem
	* Binaries are included for Windows, Linux, and OSX
	* If yours is not natively supported please download a binary from the website or file a GitHub issue so I can help
* [`git-lfs`][7] is used to store binary files
* `make` and `gcc` should be installed in order to compile the files

## Getting the Source

This project uses `git-lfs`, so please install it before cloning. If you cloned prior to installing `git-lfs`, simply run `git lfs pull` after installation.

This project is [hosted on GitHub][8]. You can clone the project directly using this command:

```
git clone --recursive git@github.com:embeddedartistry/libmemory.git
```

## Building

The library can be built by issuing the following command:

```
make
```

This will build all targets for your current architecture.

You can clean builds using:

```
make clean
```

And you can completely eliminate the generated `Makefile`s and buildresults using:

```
make purify
```

### Cross-compiling

Output is currently limited to `x86_64`, but cross-compiling for ARM will be implemented in the near future.

## Installation

Currently the best method to use this project is to build it separately and copy the contents into your tree. I will improve this method to allow easier usage as a submodule.

Copy the `include/` directory contents into your source tree.

Build artifacts are stored in the `buildresults` folder. There is a sub-folder for the target architecture (e.g. `x86_64`). Inside of this architecture you will find folders for ach type of `malloc` allocator (freelist, threadx, etc.), and a static library will be contained there.

Copy the desired library to your project and add the library to your link step.

Example linker flags:

```
-lmemory -Lpath/to/libmemory.a
```

## Usage

A block of memory needs to be initially assigned using the `malloc_addblock()` function:

```
void malloc_addblock(void* addr, size_t size);
```


This tells the malloc implementation what memory address and size to use for the heap.

```
// Allocate 4MB to the heap starting at memory address 0xDEADBEEF
malloc_addblock(0xDEADBEEF, 4 * 1024 * 1024);
```

`malloc()` and `free()` will fail (return `NULL`) if no memory has been allocated. Once memory has been allocated to the heap, you can use `malloc()` and `free()` as expected.

Multiple blocks of memory can be added using `malloc_addblock()`. The memory blocks do not have to be contiguous.

## Aligned Malloc

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

## Testing

The tests for this library are written with [CMocka][3]. You can run the tests by issuing the following command:

```
make test
```

By default, test results are generated for use by the CI server and are formatted in JUnit XML. The test results XML files can be found in `buildresults/testresults/`.

If you would prefer to see the test result summary printed to `stdout` instead, simply use the following command:

```
CMOCKA_MESSAGE_OUTPUT=stdout make test
```

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
make doc
```

Documentation can be found in `buildresults/doc`, and the root page is `index.html`.

# Need help?

If you need further assistance or have any questions, please [file a GitHub Issue][6] or send us an email using the [Embedded Artistry Contact Form][5].

# Contributing

If you are intersted in contributing to this project, please read our [contributing guidelines](docs/CONTRIBUTING.md).

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
