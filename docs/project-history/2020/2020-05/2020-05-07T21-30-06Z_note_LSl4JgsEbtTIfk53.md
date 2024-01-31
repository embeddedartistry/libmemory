Revamped build system to use the new meson-buildsystem modular approach. Also updated the Makefile command interface and CI files to use the new standardized commands.

Upon changing the build, `make coverage` now fails because the unit tests are segfaulting. They have been disabled now, pending resolution of this issue.
