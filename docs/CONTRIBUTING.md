# Contributing Guide

Welcome! We love receiving contributions from the community, so thanks for stopping by! There are many ways to contribute, including submitting bug reports, improving documentation, submitting feature requests, reviewing new submissions, or contributing code that can be incorporated into the project.

This document describes the Embedded Artistry development process. Following these guidelines shows that you respect the time and effort of the developers managing this project. In return, you will be shown respect in addressing your issue, reviewing your changes, and incorporating your contributions.

**We are actively looking for additional `malloc`/`free` implementations! Feel free to contribute!**

**Table of Contents:**

1. [Code of Conduct](#code-of-conduct)
2. [Important Resources](#important-resources)
3. [Questions](#questions)
7. [Contributing to the Project](#contributing-to-the-project)
	2. [Dependencies](#dependencies)
	3. [Development Process](#development-process)
	4. [Building the Project](#building-the-project)
	5. [Adding New Implementations](#adding-new-implementatinos)
	5. [Adding New Tests](#adding-new-tests)
9. [Community](#community)


## Code of Conduct

By participating in this project, you agree to abide by the Embedded Artistry [Code of Conduct](CODE_OF_CONDUCT.md). We expect all contributors to follow the [Code of Conduct](CODE_OF_CONDUCT.md) and to treat fellow humans with respect.

## Important Resources

This project is managed on GitHub:

* [GitHub Project Page](https://github.com/embeddedartistry/libmemory/)
* [GitHub Issue Tracker](https://github.com/embeddedartistry/libmemory/issues)

Questions can also be submitted [on the Embedded Artistry website](https://embeddedartistry.com/contact) and in the [Embedded Artistry Forum](https://embeddedartistry.com/community/embedded-artistry-oss/).

Useful Documentation:

* [Library Documentation][9]
* [cppreference (API notes)](http://en.cppreference.com)
* [C Standard Library Header Files](http://en.cppreference.com/w/c/header)

Embedded Artistry blog posts related to this project:

* [Bringup Blog Category](https://embeddedartistry.com/blog?category=Bringup) - contains multiple articles about libmemory and libc
* [Implementing Malloc: First-fit Free List](https://embeddedartistry.com/blog/2017/2/9/implementing-malloc-first-fit-free-list)
* [Implementing Malloc with ThreadX](https://embeddedartistry.com/blog/2017/2/16/implementing-malloc-with-threadx)
* [Generating Aligned Memory](https://embeddedartistry.com/blog/2017/2/20/implementing-aligned-malloc)

## Questions

Please submit your questions in the following ways:

* Filing a new [GitHub Issue](https://github.com/embeddedartistry/libmemory/issues)
* [Submitting a question on the Embedded Artistry website](https://embeddedartistry.com/contact)
* [Submitting a question on the Embedded Artistry forum](https://embeddedartistry.com/community/embedded-artistry-oss/)
* Asking a question [on Twitter: (mbeddedartistry)](https://twitter.com/mbeddedartistry/).

## New to Open Source?

If you've never worked with an open source project before, please check out our [Open Source Contribution Guide](https://embeddedartistry.com/fieldatlas/open-source-contribution-guide/), which contains information on:

* Resources for people new to open-source development
* How to find something to work on
* How to report issues
* Branching and PR guidelines for our projects
* Style guidelines for our projects

## Contributing to the Project

If you're interested in contributing = to this project, read on! Don't know where to start? Take a look at the [Open Source Contribution Guide](https://embeddedartistry.com/fieldatlas/open-source-contribution-guide/) section for information on finding beginner-friendly issues on our projects.

Please review the following guides to learn about our development process:

* [Open Source Contribution Guide](https://embeddedartistry.com/fieldatlas/open-source-contribution-guide/)
	* Resources for people new to open-source development
	- How to find something to work on
	- How to report issues
	- Branching and PR guidelines for our projects
	- Style guidelines for our projects
* [Embedded Artistry's GitHub Process](https://embeddedartistry.com/fieldatlas/embedded-artistrys-github-process/), which discusses how we handle PRs and integrate changes
* [Source Control Commit Guidelines](https://embeddedartistry.com/fieldatlas/source-control-commit-guidelines/), which describes our guidelines for commit messages

**If you have any questions about this process, please [ask us for help!](#questions)**

### Dependencies

The dependencies for [Embedded Artistry's standardized Meson build system](https://embeddedartistry.com/fieldatlas/embedded-artistrys-standardized-meson-build-system/) are described [on our website](https://embeddedartistry.com/fieldatlas/embedded-artistrys-standardized-meson-build-system/).

In addition to those dependencies, you will need the following for this repository:

* [`git-lfs`](https://git-lfs.github.com) is used to store binary files

### Development Process

`master` contains the latest code for this project, and new versions are tagged nightly.

Please branch from `master` for any new changes. Once you are ready to merge changes, open a pull request. The build server will test and analyze the branch to ensure it can be safely merged.

### Building the Project

This project uses [Embedded Artistry's standardized Meson build system](https://embeddedartistry.com/fieldatlas/embedded-artistrys-standardized-meson-build-system/). Complete instructions can be found [on our website](https://embeddedartistry.com/fieldatlas/embedded-artistrys-standardized-meson-build-system/).

### Adding New Implementations

If you area adding new files to the library that will apply across RTOSes, you will need to modify [`src/meson.build`](../src/meson.build) and add the new file to the `common_files` list.

```
common_files = [
	'aligned_malloc.c',
	'posix_memalign.c'
]
```

If you would like to create a `malloc`/`free` implementation for a new RTOS:
	* Copy the `libmemory_threadx` library target and dependency
	* Rename the build target and library output to match the RTOS
	* Add the relevant RTOS headers to the `dependencies/rtos` folder
	* Update include paths if necessary
	* Add your `malloc_*rtos*.c` file to that RTOS's build list

### Adding New Tests

If you add code you need to add tests! We’ve learned the hard way that code without tests is undependable. If your pull request reduces our test coverage because it lacks tests then it will be rejected.

This project uses CMocka as the testing framework.

Please follow these guidelines:

* New tests should be added to the [`test/src/`](../test/src) directory tree
* Each function should have its own tests in its own C file.
* When adding a new test, add the following to the relevant test coordination file:
	* Add an `extern` function declaration in [main.c](../test/main.c): `extern int ctype_tests(void);`
	* Add a call to the test coordinator in [main.c](../test/main.c): `overall_result |= ctype_tests();`

## Community

Anyone interested in active conversation regarding this project should [join the Embedded Artistry community]https://embeddedartistry.com/community/embedded-artistry-oss/).

You can also [reach out on Twitter: mbeddedartistry](https://twitter.com/mbeddedartistry/).
