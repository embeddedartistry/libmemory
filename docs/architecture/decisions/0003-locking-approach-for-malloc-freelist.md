# 3. Locking approach for malloc_freelist

Date: 2020-05-07

## Status

Accepted

## Context

The freelist implementation for `malloc` is not thread-safe. This is fine for single-threaded baremetal applications, but this library may be used in a multi-threaded application, and locking should be available.

The locking implementation should satisfy the following requirements:

- Provide single-threaded support by default, which means that users must opt-in to locking behavior
- Support optional locking behavior in a way that does not couple the library to a specific OS or locking strategy
- Handle locking/unlocking internally - do not require users to managing locking/unlocking around `malloc`/`free` calls in their application

## Decision

We will implement `malloc_lock()` and `malloc_unlock()` functions that default to weakly-linked no-op stubs in our library.

```c
_attribute__((weak)) void malloc_lock()
{
	// Intentional no-op
}

__attribute__((weak)) void malloc_unlock()
{
	// Intentional no-op
}
```

If a user needs to support thread safety, these stubs can be implemented in their application code, providing the desired locking behavior.


```c
mutex_t malloc_mutex;

void malloc_lock() 
{
	mutex_lock(&malloc_mutex);
}

void malloc_unlock()
{
	mutex_unlock(&malloc_mutex);
}
```

## Consequences

The user is responsible for knowing about these functions (by reading the documentation or reviewing the code) and supplying the proper implementations for their system.

We do not have to worry about locking implementations ourselves, since these can vary widely from one system to another. We do not have to assume any particular underlying system, which helps us retain flexibility in implementation.
