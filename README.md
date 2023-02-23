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
11. Pass performance tests to ensure time and space efficiency.

### Test Program Descriptions

### Design Properties Proven
