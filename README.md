# IPv4 Prefix Manager

A lightweight C library for managing IPv4 prefixes using a high performance trie data structure. It provides basic operations for adding, deleting, and searching IPv4 address prefixes with longest prefix match capability.

## Files

```ipv4_prefix_manager_lib.h``` - Library header with API definitions

```ipv4_prefix_manager_lib.c``` - Library implementation

```ipv4_prefix_manager_test.c``` - Test suite for core functionality

## Usage

Include the header and use the provided functions to manage your IPv4 prefixes:

```
#include "ipv4_prefix_manager_lib.h"
```

The test file demonstrates complete usage examples for all three core operations.

## Building

Compile with preferred C compiler:

```
gcc -o ipv4_prefix_manager ipv4_prefix_manager_lib.c ipv4_prefix_manager_test.c
```
