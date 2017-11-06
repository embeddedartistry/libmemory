# libmalloc

Embedded Artistry's `libmalloc` is a memory management library for embedded systems. This library provides various implemetations of the `malloc()` and `free()` functions. Other useful memory functions, such as generating aligned memory (`aligned_memory()`) are included in this library as well.

This library is meant to be coupled with the [Embedded Artistry `libc` library][1]. The definitions for `malloc()` and `free()` are included inside `libc` rather than `libmemory`.

# Requirements

* [Doxygen][0] must be installed to generate documentation
* [Premake][4] is used as the buildsystem. Binaries are included for common platforms, but if yours is not natively supported please download a binary from the website.

# Building

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

# Cross-compiling

Output is currently limited to `x86_64`, but cross-compiling for ARM will be implemented in the near future.

# Testing

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

Documentation can be built by running the following command:

```
make doc
```

Documentation can be found in `buildresults/doc`, and the root page is `index.html`.

[0]: http://www.stack.nl/~dimitri/doxygen/
[1]: https://github.com/embeddedartistry/libc
[2]: https://clang.llvm.org/docs/ClangFormat.html
[3]: https://cmocka.org
[4]: https://github.com/premake/premake-core/wiki
