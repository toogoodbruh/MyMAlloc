# MyMalloc

Maylin Horchler: mah423\
Gabe Nydick: grn22

MyMalloc guarantees 4-byte alignment. The memory array is defined using type size_t. MEMSIZE is currently defined to be 4096 divided by the size of size_t. The metadata for each chunk is 8 bytes. 4 bytes are used to store the size of the chunk and 4 bytes are used to store the chunk's allocation indicator (0 if not allocated, 1 if allocated).

mymalloc() and myfree() are implemented as described in the assignment instructions. All chunk sizes are multiples of 4. Freed chunks are immediately coalesced if applicable. Memory allocations of size 0 are not allowed and will result in an error message.

## Possible Errors

Every error message starts with "Error in < filename >, line <#>: < Error Message >", where < filename > is replaced with the name of the file from which the error-causing call to MyMalloc occurred, <#> is replaced with the line number on which the error-causing call to MyMalloc occurred, and < Error Message > is replaced with any of the following error messages:

1. "Allocation of 0 bytes is not allowed."
        Occurs when an attempt to allocate 0 bytes of memory is made.
2. "Allocation is bigger than total memory."
        Occurs when an attempt to allocate more bytes of memory than MEMSIZE is made.
3. "Not enough memory."
        Occurs when an attempt to allocate more bytes of memory than the size of the biggest non-allocated chunk is made.
4. "Invalid address - this address is not from malloc()."
        Occurs when an attempt to free memory at an address not within the memory array is made.
5. "Memory already free."
        Occurs when an attempt to free memory that is already free is made.
6. "Invalid address - this address is not the start of a chunk."
        Occurs when an attempt to free memory at an address not at the beginning of a chunk is made.

## Test Plan
MyMalloc must:
1. Guarantee 4-byte alignment
2. Keep all chunks allocated within the memory array
3. Not have overlapping chunks
4. Allocate a chunk for any non-error producing call of malloc()
5. Return a pointer to the allocated chunk's payload for any non-error producing call of malloc()
6. Split a bigger chunk into two smaller chunks upon memory allocation where possible
7. De-allocate a chunk for any non-error producing call of free()
8. Coalesce adjacent free chunks upon freeing any chunk where possible
9. Report errors in the appropriate format when they occur
10. Not require an initialize function before using other functions in the library
11. Pass performance tests to ensure time and space efficiency

### Test Program Descriptions

allocateZero(): tries to allocate zero
allocateLargeMemory(): tries to allocate memory larger than mymalloc can hold
overlapCheck(): checks that two given chunks are not overlapping
addressDivBy4(): checks that all addresses in memory are divisible by 4
chunkLocCheck(): checks that chunk locations are all within memory
freeOutsideMem(): tries to free memory outside of memory allocation
freeNonChunk(): tries to free memory not starting at a chunk
freeTwice(): tries to free memory more than once

main(): Runs script testing design properties
- tries to allocate 0
- tries to allocate bigger than memory
- randomly fills array with 49 chunks of size 10 up to size 64
- tries to make chunk bigger than remaining chunk
- tries to allocate 0
- makes a final chunk filling the rest of the array
- tries to allocate 0
- tries to allocate bigger than memory
- tries to allocate 1, showing malloc is full
- proves no chunks overlap, all addresses are divisible by 4, and that no chunks go outside allocated memory
- tries to free just 1 char outside memory on both sides of memory
- tries to free addresses outside of chunks
- frees first & last chunk
- frees memory in random order until whole memory is free
- allocates a chunk taking whole memory
- frees chunk

### Design Properties Proven
If there are no correctness errors found when running test.c, the design properties under Test Plan are proven.
