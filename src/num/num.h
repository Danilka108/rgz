#include "../config.h"

#ifndef RGZ_1_NUM_H
#define RGZ_1_NUM_H

typedef long long int Num_chunk;

struct Num
{
    int len;
    Signs sign;
    Num_chunk *chunks;
};

Num *create_num(int len, Signs sign = Signs::positive);

Num *copy_num(Num *num);

Num *get_num_slice(Num *num, int slice_start, int slice_end);

int get_num_chunk_len(Num_chunk num_chunk);

Num *add_zeros_to_num(Num *num, int zeros_count);

#endif //RGZ_1_NUM_H