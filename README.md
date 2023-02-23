# MyMalloc

Maylin Horchler, Gabe Nydick
mah423, grn22

MyMalloc guarantees 4-byte alignment. The memory array is defined using type size_t. MEMSIZE is currently defined to be 4096 divided by the size of size_t. The metadata for each chunk is 8 bytes. 4 bytes are used to store the size of the chunk and 4 bytes are used to store the chunk's allocation indicator (0 if not allocated, 1 if allocated).

mymalloc() and myfree() are implemented as described in the assignment instructions. All chunk sizes are multiples of 4. Freed chunks are immediately coalesced if applicable. Memory allocations of size 0 are not allowed and will result in an error message.

Every error message starts with "Error in <filename>, line <#>: <Error Message>", where <filename> is replaced with the name of the file from which the error-causing call to mymalloc occurred, <#> is replaced with the line number on which the error-causing call to mymalloc occurred, and <Error Message> is replaced with any of the following error messages:

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

Test Plan:

Test Program Descriptions:

Design Properties Proven:

Design Notes: