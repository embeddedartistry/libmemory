# 2. Expect external libc to be supplied through subproject or cross file

Date: 2020-05-07

## Status

Accepted

## Context

This project is designed to be used along with a `libc` implementation. The odds are good that if someone is using this library, they are not using the standard `libc` that ships with their compiler. This library needs to know about the particular `libc` implementation during its build, in case there are important differences in definitions.

## Decision

Previously, a path to the `libc` headers was provided. We are now expecting the `libc` dependency to be handled in one of two ways:

1. Included as a Meson subproject, which can be specified through `meson_options.txt` for user customization
2. Added as `c_stdlib` in a Meson cross-file that is used to build the project.
3. Handled via the `*_args` and `*_link_args` flags in the Meson cross-file that is used to build the project.

This provides the most flexible approach to managing the external `libc` dependency.

## Consequences

It is more difficult to now specify a raw relative path to `libc` headers, since the user must manually implement the necessary flags in a cross file if that is the desired approached. This might be complex.

This approach requires additional familiarity with the Meson build system, both in handling subprojects and in writing cross files.
