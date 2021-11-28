#include <cmath>
#include "../config.hpp"

#ifndef RGZ_1_NUM_H
#define RGZ_1_NUM_H

typedef long long int Num_chunk;

typedef struct
{
    size_t len;
    Signs sign;
    Num_chunk *chunks;
} Num;

Num *create_num(size_t, Signs = Signs::positive);

Num *create_num_from_num_chunk(Num_chunk);

Num *copy_num(Num *);

void update_num(Num **, Num *);

void concat_num(Num **, Num *);

void trim_num_zeros(Num **);

Num *get_num_slice(Num *, size_t, size_t);

void add_zero_chunks_to_num(Num **, size_t);

Comparison_flags compare_unsigned_nums(Num *, Num *);

size_t get_num_chunk_len(Num_chunk);

size_t get_nums_delta_len(Num *, Num *);

#endif //RGZ_1_NUM_H