# Malloc

Dynamic memory allocation management library.

## Description

The goal of this C project is to write our own dynamic library to replace the existing libc functions: `malloc`, `free` and `realloc`. This gives us an overview of how the original functions are implemented, and forces us to have a deeper understanding of memory management within an operating system and a computer.

![Diagram](img/diagram.png)

As shown in the diagram, memory is arranged into zones of different sizes, which may contain 1 or more blocks of memory. A global doubly linked list of metadata is used to contain all the information on zones and blocks created during the program's lifetime. These metadata are added at the head of each zone and block in order to retain information specific to them (size, type, etc.).

In order to optimize performance and avoid having to call `mmap` each time a new allocation request is made, memory zones (tiny and small) are preallocated to contain a minimum of 100 memory blocks of max size x. So when an user requests an allocation whose max size corresponds to one of these 2 zones, a new memory block within these zones will be created (if possible) rather than a new zone. If the requested size is greater than the max value of a small block, then a big zone is simply created, containing only one memory block.

A memory zone is deleted with `munmap` once all the blocks inside have been freed. To avoid fragmentation of memory, continuous blocks are merged together if both are not used anymore (and if their combined size doesn't exceed the max size).

Some additionnal information about this library:
- the pointer address returned by malloc is aligned to 16 bytes.
- 1 tiny and small zone are always preallocated in order to limit calls to `mmap` if only 1 zone ever exists
- `show_alloc_mem` and `show_alloc_mem_ex` display the current state of the allocated zones and blocks on the terminal
- all the functions from this library are thread-safe
- the default behavior of the library can be modified with 2 environment variables, `FT_MALLOC_MAX_ZONES` (maximum number of allocated zones) and `FT_MALLOC_MAX_SIZE` (maximum size of an allocation)

## Usage

```bash
# build the shared library
make

# build and run the tests
cd tests && make && ./tests
```
