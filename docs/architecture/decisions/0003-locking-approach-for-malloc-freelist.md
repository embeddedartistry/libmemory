# 3. Locking approach for malloc_freelist

Date: 2020-05-07

## Status

Accepted

## Context

The freelist implementation for `malloc` is not threadsafe.

## Decision

We will implement `__malloc_lock()` and `__malloc_unlock()` functions that default to weakly-linked no-op stubs in our library.

If a user needs to support thread safety, these stubs can be implemented in their system to provide locking behavior.

## Consequences

The user is responsible for knowing about these functions (by reading the documentation or reviewing the code) and supplying the proper implementations for their system.

We do not have to worry about locking implementations ourselves, since these can vary widely from one system to another. We do not have to assume any particular underlying system, which helps us retain flexibility in implementation.
