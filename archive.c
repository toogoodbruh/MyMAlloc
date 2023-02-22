//old code, saving for possible future use

typedef struct {
    unsigned size;
    bool alloc_status; //1 if free, 0 if allocated
} chunk_header;